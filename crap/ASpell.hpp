#pragma once

#include <iostream>

class ATarget;

class ASpell {
    protected:
        std::string name;
        std::string effects;
    
    public:
        ASpell();
        ASpell& operator=(const ASpell& other);
        ASpell(const ASpell& other);

        const std::string& getName() const;
        const std::string& getEffects() const;
        virtual ~ASpell();
        virtual ASpell* clone() const = 0;

        ASpell(std::string name, std::string effects);
        void launch(const ATarget& target) const;
};
