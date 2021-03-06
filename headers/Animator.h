#pragma once

#include <SFML/System.hpp>
#include <functional>
#include <vector>

class GInterpolation {
public:
    enum Easing{
        Linear,
        InOut,
        In,
        Out
    };

    GInterpolation(float rate);
    GInterpolation(float rate, std::function<void()> cb);
    GInterpolation(float rate, std::function<void()> cb, Easing e);
    bool hasEnded() const;
    //I wanted this to be pure, but it wont work
    virtual void step(sf::Time dt) = 0;
protected:
    float rate;
    float alpha = 0;
    bool ended = false;
    Easing easing = Easing::Linear;
    std::function<void()> cb = [](){};
};

template<class T> 
class Interpolation : public GInterpolation {
public:
    Interpolation(T& i, T t, float r) : 
    GInterpolation(r)
    {
        original = i;
        interpolated = &i;
        target = t;
    };
    Interpolation(T& i, T t, float r, std::function<void()> ca) : 
    GInterpolation(r, ca)
    {
        original = i;
        interpolated = &i;
        target = t;
    };
    Interpolation(T& i, T t, float r, std::function<void()> ca, GInterpolation::Easing e) : 
    GInterpolation(r, ca, e)
    {
        original = i;
        interpolated = &i;
        target = t;
    };
    virtual void step(sf::Time dt) override;
    float lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    };
private:
    T* interpolated;
    T target;
    T original; //Original value before interpolation
};


class Animator {
public:
    Animator();
    void interpolate(GInterpolation& i);
    void update(sf::Time dt);
private:
    std::vector<GInterpolation*> interpolations;
};
