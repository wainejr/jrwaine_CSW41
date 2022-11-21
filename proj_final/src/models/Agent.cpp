#include "./Agent.h"

using namespace models;

void Agent::update_position() {
  auto sum_val = this->direction.mul(this->vel);
  this->pos.add(sum_val);
}
