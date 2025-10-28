#pragma once
#include <string>

class HitComponent {
protected:
  std::string uuid;

public:
  HitComponent() : uuid{/* TODO: Generate uuid */} { };
  ~HitComponent() = default;

  virtual bool Hit() const = 0;
  virtual void Add(HitComponent &in) {}
  virtual void Remove(HitComponent &in) {}
  bool operator==(const HitComponent &other) const {
    return uuid == other.uuid;
  }
};