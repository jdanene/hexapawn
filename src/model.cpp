#include "model.h"

namespace hexapawn {


    Player other_player(Player p)
    {
        switch (p) {
            case Player::first:
                return Player::second;
            case Player::second:
                return Player::first;
            default:
                throw ge211::Client_logic_error("other_player: not a player")
        }

    }




}