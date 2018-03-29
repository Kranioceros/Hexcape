#include "TablaPuntajes.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstring>
#include <algorithm>

TablaPuntaje::TablaPuntaje(std::string _nombre_archivo, unsigned int puntuacion) {

  /* Se inicializan algunos atributos */
  nombre_jugador.resize(20, '\0');
  nombre_jugador[0] = nombre_jugador[1] = nombre_jugador[2] = 'A';
  puntos_jugador = puntuacion;
  nombre_archivo = _nombre_archivo;
  estado = INGRESANDO;
  font.loadFromFile("fonts/munro.ttf");
  font_mono.loadFromFile("fonts/COURIER.TTF");
  pos_cursor = 0;
  periodo_cursor = 500;
  periodo_delay = 200;
  timer_cursor.restart();
  cursor_mostrar = true;

  /* Se leen las puntuaciones existentes */
  leerPuntaje();
}

bool TablaPuntaje::leerPuntaje() {
  std::ifstream archivo_in(nombre_archivo, std::ios::binary | std::ios::in);
  if(!archivo_in.is_open()) {
    /* Se crea el archivo en cuestion */
    std::ofstream archivo_out(nombre_archivo, std::ios::binary);
    archivo_out.close();
    std::cout << "El archivo no existe, se crea uno nuevo..." << std::endl;
    return false;
  } else {
    archivo_in.seekg(0);
    Entrada tmp;
    while(archivo_in.read(reinterpret_cast<char*> (&tmp), sizeof(Entrada))) {
      tabla.push_back(tmp);
      std::cout << "Se ha leido una entrada: " << std::endl;
      std::cout << "Nombre: " << tmp.nombre << std::endl
                << "Puntuacion: " << tmp.puntos << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
  }
  return true;
}

void TablaPuntaje::escribirPuntaje() {
  std::ofstream archivo_out(nombre_archivo, std::ios::binary);
  for(const Entrada &e : tabla) {
    archivo_out.write(reinterpret_cast<const char*>(&e), sizeof(Entrada));
    std::cout << "Se ha escrito una entrada:" << std::endl;
    std::cout << "Nombre: " << e.nombre << std::endl
              << "Puntuacion: " << e.puntos << std::endl;
  }
  std::cout << "---------------------------------" << std::endl;
}

void TablaPuntaje::dibujar(float x, float y, sf::RenderWindow &w) {
  std::stringstream instrucciones_ss;
  if (estado == INGRESANDO) {
    std::stringstream nombre_jugador_ss;
    nombre_jugador_ss << std::left << std::setw(20) << nombre_jugador.c_str();
    sf::Text nombre_jugador_text(nombre_jugador_ss.str(), font_mono, 50);
    std::stringstream prompt_ss;
    prompt_ss << "Tu puntuacion fue " << puntos_jugador << ". Ingresa tu nombre:";
    sf::Text prompt(prompt_ss.str(), font, 24);
    std::string cursor(20, ' '); cursor[pos_cursor] = '^';
    sf::Text cursor_text(cursor, font_mono, 50);
    instrucciones_ss << "El cursor se puede mover usando las teclas de direccion. Presiona <Enter> para confirmar el nombre";

    prompt.setOrigin(prompt.getLocalBounds().width / 2,
                     prompt.getLocalBounds().height / 2);
    nombre_jugador_text.setOrigin(nombre_jugador_text.getLocalBounds().width / 2,
                                  nombre_jugador_text.getLocalBounds().height / 2);
    cursor_text.setOrigin(cursor_text.getLocalBounds().width / 2,
                          cursor_text.getLocalBounds().height / 2);

    prompt.setPosition(x, y);
    nombre_jugador_text.setPosition(x, y + 100);
    cursor_text.setPosition(x, y+150);

    w.draw(prompt);
    w.draw(nombre_jugador_text);
    if (cursor_mostrar)
      w.draw(cursor_text);
  } else if (estado == ESTATICO){

    instrucciones_ss << "Presiona <Enter> para jugar de nuevo. Presiona <Esc> para salir";

    auto it_jugador =
      std::find_if(tabla.begin(),
                   tabla.end(),
                   [this](Entrada x) { return strcmp(this->nombre_jugador.c_str(), x.nombre) == 0;}
                   );

    if (it_jugador != tabla.end()) {
      /* Primera fila de la tabla con las etiquetas */
      std::stringstream tabla_ss;
      tabla_ss << std::left << std::setw(8)  << std::setfill(' ') << "Puesto"
               << std::left << std::setw(25) << std::setfill(' ') << "Nombre"
               << std::left << std::setw(10) << std::setfill(' ') << "Puntuacion"
               << "\n\n\n";

      /* Se obtiene el puesto del jugador en la tabla */
      unsigned int puesto_jugador = it_jugador - tabla.begin();

      /* Si el jugador esta en el undecimo puesto o mas, se muestran los 9 puestos anteriores
         y al jugador */
      if (tabla.size() > 10 && puesto_jugador > 9) {
        auto it_primero = it_jugador - 9;
        unsigned int pos = puesto_jugador - 9 + 1;

        for (auto it = it_primero; it < it_jugador + 1; it++) {
         tabla_ss 
           << std::left << std::setw(8)  << std::setfill(' ') << pos
           << std::left << std::setw(25) << std::setfill(' ') << it->nombre
           << std::left << std::setw(10) << std::setfill(' ') << it->puntos
           << std::endl;
         pos++;
        }
      } else {
        unsigned int pos = 1;
        for (auto it = tabla.begin(); it < tabla.end(); it++) {
          tabla_ss
            << std::left << std::setw(8)  << std::setfill(' ') << pos
            << std::left << std::setw(25) << std::setfill(' ') << it->nombre
            << std::left << std::setw(10) << std::setfill(' ') << it->puntos
            << std::endl;
          pos++;
        }
      }
      sf::Text tabla_text(tabla_ss.str(), font_mono, 24);
      tabla_text.setOrigin(tabla_text.getLocalBounds().width / 2,
                           tabla_text.getLocalBounds().height / 2);
      tabla_text.setPosition(x, y);

      w.draw(tabla_text);
    }
  }
  sf::Text instrucciones_text(instrucciones_ss.str(), font, 32);
  instrucciones_text.setOrigin(instrucciones_text.getLocalBounds().width / 2,
                               instrucciones_text.getLocalBounds().height / 2);
  instrucciones_text.setPosition(x, y + 500);

  w.draw(instrucciones_text);
}

void TablaPuntaje::actualizar(sf::Event e) {
  if(estado == ESTATICO) {
    if(timer_delay.getElapsedTime().asMilliseconds() > periodo_delay &&
       sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
      estado = SALIENDO;
    }
  }
  else if (estado == INGRESANDO){
    if(e.type == sf::Event::TextEntered) {
      /* Si el jugador ingreso un caracter ASCII imprimible */
      if(e.text.unicode > 32 && e.text.unicode < 127) {
        nombre_jugador[pos_cursor] = static_cast<char>(e.text.unicode);
        pos_cursor = pos_cursor < 19 ? (pos_cursor+1) : pos_cursor;
      }
      /* Si el jugador presiono backspace, se borra un caracter */
      if(e.text.unicode == 8) {
        if(nombre_jugador[pos_cursor] == '\0' &&
           pos_cursor > 0 &&
           nombre_jugador[pos_cursor-1] != '\0')
          {
            pos_cursor--; 
            nombre_jugador[pos_cursor] = '\0';
          }
      }
    }
    /* Si el jugador toco una flecha para mover el cursor */
    if(e.type == sf::Event::KeyPressed) {
      if(e.key.code == sf::Keyboard::Right) {
        unsigned int nueva_pos = (pos_cursor + 1) % 20;
        if (nombre_jugador[pos_cursor] != '\0')
          pos_cursor = nueva_pos;
      }
      if(e.key.code == sf::Keyboard::Left) {
        unsigned int nueva_pos = pos_cursor > 0 ? (pos_cursor - 1) : 19;
        if (nombre_jugador[nueva_pos] != '\0')
          pos_cursor = nueva_pos;
      }
    }
    /* Si el jugador presiono enter */
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
      estado = ESTATICO;
      Entrada tmp;
      strcpy(tmp.nombre, nombre_jugador.c_str());
      tmp.puntos = puntos_jugador;

      /* Si no se encuentra otra entrada exactamente igual, se agrega */
      auto it_identico = std::find_if(tabla.begin(),
                                      tabla.end(),
                                      [&tmp](Entrada x) {
                                        return x.puntos == tmp.puntos && strcmp(x.nombre, tmp.nombre) == 0;});
      if (it_identico == tabla.end()){
        /* Se agrega a la tabla y se reordena */
        tabla.push_back(tmp);
        std::sort(tabla.begin(),
                  tabla.end(),
                  [](Entrada x, Entrada y) { return x.puntos > y.puntos; });
      }

      timer_delay.restart();
    }
    /* Se actualiza el timer del cursor */
    if (timer_cursor.getElapsedTime().asMilliseconds() > periodo_cursor) {
      timer_cursor.restart();
      cursor_mostrar = !cursor_mostrar;
    }
  }
}

bool TablaPuntaje::quiereSalir() {
  return estado == SALIENDO;
}
