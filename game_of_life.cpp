#include "game_of_life.h"

GameOfLife::GameOfLife(int lines, int columns)
    : torus_(lines, std::vector<bool>(columns, false)) {
}

int GameOfLife::lines() const {
  return torus_.size();
}

int GameOfLife::columns() const {
  return torus_[0].size();
}

void GameOfLife::Enliven(int i, int j) {
  if( i < 0 || i >= lines() || j < 0 || j >= columns() ) throw InvalidCellException{i, j};
  torus_[i][j] = true;
}

void GameOfLife::Kill(int i, int j) {
  if( i < 0 || i >= lines() || j < 0 || j >= columns() ) throw InvalidCellException{i, j};  
  torus_[i][j] = false;
}

bool GameOfLife::alive(int i, int j) const {
  if( i < 0 || i >= lines() || j < 0 || j >= columns() ) throw InvalidCellException{i, j};  
  return torus_[i][j];
}


void GameOfLife::operator++(int) {

  vector<vector<bool>> new_torus(lines(), std::vector<bool>(columns(), false));

  for (int i = 0; i < lines(); i++) {
    for (int j = 0; j < columns(); j++) {
      new_torus[i][j] = lives(i, j);
    }
  }

  torus_ = new_torus;
}


int GameOfLife::neighbors(int i, int j) const {

  if( i < 0 || i >= lines() || j < 0 || j >= columns() ) throw InvalidCellException{i, j};
  int n = 0;
  
  for (int x : {-1, 0, 1}) {
    for (int y : {-1, 0, 1}) {
      // Soma o valor de lines() (resp. columns()) ao valor de i + x
      // (resp. j + y) para o caso onde x (resp. y) é negativo.            
      int neighbor_i = (i + x + lines()) % lines();
      int neighbor_j = (j + y + columns()) % columns();
      
      // Erro Detectado: o método estava contabilizando a própria célula como vizinha
      if (alive(neighbor_i, neighbor_j)  &&  !(x == 0  &&  y == 0) ) {  
        n++;
      }
    }
  }

  return n;
}



bool GameOfLife::lives(int i, int j) const {

  if( i < 0 || i >= lines() || j < 0 || j >= columns() ) throw InvalidCellException{i, j};

  int n = neighbors(i, j);

  if (alive(i, j)) {
    return n == 2 || n == 3;
  } else {
    return n == 3;
  }
}