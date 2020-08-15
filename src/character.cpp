/*
 *  Copyright (C) 2020  Gabriele A. Ron
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "libeztp/character.hpp"

eztp::character::character(const std::string &initname, const std::string &initclass,
                           const std::string &initrace,
                           const std::string &initbg, int level, int strength, int dexterity,
                           int constitution,
                           int intelligence, int wisdom, int charisma, bool isNPC, unsigned long id) {
    /**
     * Creates the character with basic attributes and stats in an easy constructor
     *
     * Very basic and does not include equipment or spells, nor does it return anything
     *
     * @param initname The name of the character
     * @param initclass The class of the character
     * @param initrace The race of the character
     * @param initbg The background of the character
     *
     * @param level The character level
     *
     * @param strength The character's strength (Default 10)
     * @param dexterity The character's dexterity (Defult 10)
     * @param constitution The character's constitution (Default 10)
     * @param intelligence The character's intelligence (Default 10)
     * @param wisdom The character's wisdom (Default 10)
     * @param charisma The character's charisma (Default 10)
     *
     * @param isNPC Demarcates whether this is an NPC or PC
     */

    uid = id;

    name = initname;
    crace = initrace;
    cclass = initclass;
    cbg = initbg;
    clevel = level;
    npc = isNPC;

    if (uid) {
        setRace(crace);
        setBG(cbg);
    }
}

bool eztp::character::operator==(const character &a) const {
    return uid == a.uid;
}

eztp::character &eztp::character::operator=(const character &a) {
    /**
     * Overriding the assignment operator to copy characters completely
     *
     * @param a The input character
     *
     * @return The copied character
     */

    npc = a.npc;

    name = a.name;
    crace = a.crace;
    cclass = a.cclass;
    cbg = a.cbg;
    clevel = a.clevel;

    abilities = a.abilities;

    hp = a.hp;
    ac = a.ac;
    gp = a.gp;
    speed = a.speed;

    equipment = a.equipment;
    misc = a.misc;
    proBonus = a.proBonus;
    proficiencies = a.proficiencies;
    traits = a.traits;
    saves = a.saves;
    languages = a.languages;

    size = a.size;

    vulnerabilities = a.vulnerabilities;
    resistances = a.resistances;
    immunities = a.immunities;
    conditions = a.conditions;

    uid = a.uid;

    return *this;
}

void eztp::character::softCopy(const character &a) {
    /**
     * Soft copies the character
     *
     * Essentially copies equipment; That's all
     *
     * @param a The input character
     *
     * @return The soft copy of the character
     */

    gp = a.gp;

    equipment = a.equipment;
    misc = a.misc;
}

void eztp::character::addTrait(const std::string &name, const std::string &description) {
    traits.emplace(name, description);
}

void eztp::character::delTrait(const std::string &name) {
    traits.erase(name);
}

void eztp::character::addProf(const std::string &name) {
    proficiencies.push_back(name);
}

void eztp::character::delProf(const std::string &name) {
    proficiencies.erase(remove(proficiencies.begin(), proficiencies.end(), name), proficiencies.end());
}

void eztp::character::addItem(const std::string &name) {
    misc.push_back(name);
}

void eztp::character::delItem(const std::string &name) {
    misc.erase(remove(misc.begin(), misc.end(), name), misc.end());
}

void eztp::character::addCondition(const std::string &name) {
    conditions.push_back(name);
}

void eztp::character::delCondition(const std::string &name) {
    conditions.erase(remove(conditions.begin(), conditions.end(), name), conditions.end());
}

void eztp::character::setWeapon(const std::string &inWeapon) {
    equipment[0] = inWeapon;
}

void eztp::character::setArmor(const std::string &inArmor) {
    equipment[1] = inArmor;
}

std::string eztp::character::getWeapon() {
    /**
     * Gets the weapon name
     *
     * @return The weapon name
     */

    return equipment[0];
}

std::string eztp::character::getArmor() {
    /**
     * Gets the armor name
     *
     * @return The armor name
     */

    return equipment[1];
}

int eztp::character::attack(bool mod) {
    /**
     * Used to get the damage from a weapon attack
     *
     * @param mod Whether to add the ability modifier or not; default true
     *
     * @return the damage
     */

    Weapons::WeaponStruct weap = Weapons::getWeapon(equipment[0]);

    int att = weap.ability;
    int abi = (att == 1) ? (abilities.at("DEX") / 2) + 1 : (att == 2) ? (abilities.at("STR") / 2) + 1 : (att == 3)
                                                                                                        ? ((abilities.at("DEX")/2) + 1 >=
                                                                                                           (abilities.at("STR")/2) + 1)
                                                                                                          ? (abilities.at("DEX")/2) + 1
                                                                                                          : (abilities.at("STR")/2) + 1
                                                                                                        : 0;

    int dmg;

    mod ? dmg = abi : dmg = 0;

    for (int i = 0; i < weap.numberDice; ++i) {
        dmg += weap.die.roll();
    }

    return dmg;
}

int eztp::character::rollSkill(const std::string &skill) {
    /**
     * Returns a random dice roll for the provided skill
     *
     * @param skill The skill to roll for
     *
     * @return The roll with skill & proficiency if applicable
     */

    int x = abilities.at(skills.at(skill)) / 2 + 1;

    if (std::count(proficiencies.begin(), proficiencies.end(), skill)) {
        x += proBonus;
    }

    return dice.at(20).roll() + x;
}

void eztp::character::setRace(const std::string &name) {
    /**
     * Sets the race and abilities and stuff
     *
     * DO NOT RUN AFTER CONSTRUCTION
     */

    Race::RaceStruct x = Race::getRace(name);

    for (unsigned long i = 0; i < x.abis.size(); ++i) {
        if (x.abis[i] == "HP") {
            hp += x.boosts[i];
        } else {
            abilities.at(x.abis[i]) += x.boosts[i];
        }
    }

    size = x.size;
    speed = x.speed;

    traits.insert(x.traits.begin(), x.traits.end());
    proficiencies.insert(proficiencies.end(), x.prof.begin(), x.prof.end());
}

void eztp::character::setBG(const std::string &name) {
    Background::BackgroundStruct x = Background::getBg(name);

    gp = x.gp;

    proficiencies.insert(proficiencies.end(), x.prof.begin(), x.prof.end());
    misc.insert(misc.end(), x.equip.begin(), x.equip.end());
}