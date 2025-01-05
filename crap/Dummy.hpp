#pragma once

class ATarget;

class Dummy: public ATarget {
    public:
     Dummy();
     Dummy& operator=(const Dummy& other);
     Dummy(const Dummy& other);

     ~Dummy();
     ATarget* clone() const;
};
