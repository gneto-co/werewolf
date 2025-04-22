#include "../includes/Player.hpp"

Player::Player(int card, int id, std::string name) : _card(card), _id(id), _real_name(name)
{
    _status = ALIVE;
    _target_id = 0;
    _role = card;
}

Player::Player() {}

Player::~Player() {}

/* GETTERS */

int Player::getRole() const { return _role; }
int Player::getRoleCard() const { return _card; }
int Player::getStatus() const { return _status; }
int Player::getKilledBy() const { return _killed_by; }
int Player::getTargetId() const { return _target_id; }
int Player::getId() const { return _id; }
std::string Player::getRealName() const { return _real_name; }

/* SETTERS */
void Player::setRole(int role) { _role = role; }
void Player::setTargetId(int target_id) { _target_id = target_id; }
void Player::setStatus(int status) { _status = status; }
void Player::setKilledBy(int killed_by) { _killed_by = killed_by; }