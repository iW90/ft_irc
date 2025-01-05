#pragma once

#include <iostream>

class ASpell;

class ATarget {
    protected:
        std::string type;

    public:
        ATarget();
        ATarget& operator=(const ATarget& other);
        ATarget(const ATarget& other);
        const std::string& getType() const;

        virtual ~ATarget();
        virtual ATarget* clone() const = 0;

        Atarget(std::string type);
        void getHitBySpell(const ASpell& spell) const;
};