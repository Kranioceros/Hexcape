#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class TablaPuntaje {
public:
  /* Carga archivo de puntaje. Si no existe, lo crea */
  TablaPuntaje(std::string archivo_puntaje, unsigned int puntuacion);
  bool leerPuntaje();
  bool quiereSalir();
  void escribirPuntaje();
  void actualizar(sf::Event e);
  void dibujar(float x, float y, sf::RenderWindow &w);
private:
  enum { INGRESANDO, ESTATICO, SALIENDO } estado;
  struct Entrada {
    unsigned int puntos;
    char nombre[21];
  };

  std::vector<Entrada> tabla;
  std::string nombre_jugador;
  unsigned int puntos_jugador;
  std::string nombre_archivo;
  sf::Font font;
  sf::Font font_mono;
  unsigned int pos_cursor;
  sf::Clock timer_cursor;
  sf::Clock timer_delay;
  float periodo_cursor;
  float periodo_delay;
  bool cursor_mostrar;
};
