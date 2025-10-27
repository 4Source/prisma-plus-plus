#pragma once

class Component {
protected:
public:
    Component() = default;
    ~Component() = default;
    
    virtual bool Hit() const = 0;
    virtual void Add(Component in) {}
    virtual void Remove(Component in) {}
};