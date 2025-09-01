#include "WindRule.h"
#include <imgui.h>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f WindRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // todo: add a wind force here
  // hint: use the windAngle variable

  Vector2f windDirection(cos(windAngle), sin(windAngle));
  float windStrength = 1.0f;
  Vector2f windForce = windDirection * windStrength;

  return windForce;
  //return Vector2f::zero();

  //Maybe return and make wind strength stronger?
}

bool WindRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::SliderAngle("Wind Direction", &windAngle, 0)) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}