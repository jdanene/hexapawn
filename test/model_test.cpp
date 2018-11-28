#include <model.h>
//#include <controller.h>
#include <view.h>
#include <catch.h>
#include <iostream>

using namespace hexapawn;
TEST_CASE("Check that defaults are correct") {
    Model hexapawn(8, 8);
    
    //Ensure that the bottom row corresponds to P1 and top row to P2
    CHECK(hexapawn.get_ele({0, 0}) == Player::second);
}




// Correct turn?
// CHECK( hexapawn.get_turn() == Player::second);
// Correct winner?
//CHECK( hexapawn.game_over() == Player::neither);



//Viable Moves
//CHECK(connect_four.is_viable_p({0,7},{0,6},Player::first)); //P1: forward to an empty square
//CHECK(connect_four.is_viable_p({0,0},{0,1},Player::second)); //P2: forward to an empty square

//Not Viable Moves
//CHECK(!connect_four.is_viable_p({0,7},{0,6},Player::first)); //P1: left boundary pawn {0,7} => to upper left kill {-1,6}
//CHECK(!connect_four.is_viable_p({0,7},{0,6},Player::first)); //P1: right boundary pawn {4,7} => to upper right kill {5,6}




//CHECK(!connect_four.is_viable_p({0,7},{0,6},Player::first)); //P1: pawn => upper left kill without enemy pawn
//CHECK(!connect_four.is_viable_p({0,7},{0,6},Player::first)); //P1: pawn => upper right kill without enemy pawn
//CHECK(!connect_four.is_viable_p({0,7},{0,6},Player::first)); //P2: pawn => upper left kill without enemy pawn
// CHECK(!connect_four.is_viable_p({0,7},{0,6},Player::first)); //P2: pawn => upper right kill without enemy pawn




/*
TEST_CASE("can create other sizes")
{
Model c2(2, 5, 4);
CHECK( c2.k() == 2 );
CHECK( c2.m() == 5 );
CHECK( c2.n() == 4 );

Model c3(3, 6, 5);
CHECK( c3.k() == 3 );
CHECK( c3.m() == 6 );
CHECK( c3.n() == 5 );

Model c5(5, 8, 7);
CHECK( c5.k() == 5 );
CHECK( c5.m() == 8 );
CHECK( c5.n() == 7 );
}

TEST_CASE("can move")
{
using Column = std::vector<Player>;

Model c2(2, 5, 4);

CHECK( c2.get_turn() == Player::first );
CHECK( c2.get_winner() == Player::neither );
c2.place_token(0);
CHECK( c2.get_column(0) == Column{Player::first} );

CHECK( c2.get_turn() == Player::second );
c2.place_token(1);
CHECK( c2.get_column(1) == Column{Player::second} );

CHECK( c2.get_turn() == Player::first );
c2.place_token(2);
CHECK( c2.get_column(2) == Column{Player::first} );

CHECK( c2.get_turn() == Player::second );
c2.place_token(0);
CHECK( c2.get_column(0) == Column{Player::first, Player::second} );

CHECK( c2.get_turn() == Player::neither );
CHECK( c2.get_winner() == Player::second );

CHECK_THROWS_AS(c2.place_token(0), ge211::Client_logic_error);
}

TEST_CASE("full column throws")
{
Model c2(2, 5, 4);

c2.place_token(0);
c2.place_token(0);
c2.place_token(0);
c2.place_token(0);
CHECK_THROWS_AS(c2.place_token(0), ge211::Client_logic_error);

c2.place_token(2);
c2.place_token(2);
c2.place_token(2);
c2.place_token(2);
CHECK_THROWS_AS(c2.place_token(2), ge211::Client_logic_error);

c2.place_token(1);
CHECK_THROWS_AS(c2.place_token(1), ge211::Client_logic_error);
}*/