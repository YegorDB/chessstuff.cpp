#include "test_handler.h"

void testValidatePosition() {
    assert_error_was_thrown(
        [](){
            Handler{FEN{"p3k3/8/8/8/8/8/8/4K3 w - - 0 1"}};
        },
        "Pawn on first row at a8."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/8/4K2P w - - 0 1"}};
        },
        "Pawn on first row at h1."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/8/4KK2 w - - 0 1"}};
        },
        "Incorrect white kings number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"3kk3/8/8/8/8/8/8/4K3 w - - 0 1"}};
        },
        "Incorrect black kings number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/QQQQQQQQ/QQ2K3 w - - 0 1"}};
        },
        "Incorrect white queens number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k1qq/qqqqqqqq/8/8/8/8/3PPP2/4K3 w - - 0 1"}};
        },
        "Incorrect black queens number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/RRRRRRRR/RRR1K3 w - - 0 1"}};
        },
        "Incorrect white rooks number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4krrr/rrrrrrrr/8/8/8/8/3PPP2/4K3 w - - 0 1"}};
        },
        "Incorrect black rooks number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/BBBBBBBB/BBB1K3 w - - 0 1"}};
        },
        "Incorrect white bishops number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4kbbb/bbbbbbbb/8/8/8/8/3PPP2/4K3 w - - 0 1"}};
        },
        "Incorrect black bishops number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/NNNNNNNN/NNN1K3 w - - 0 1"}};
        },
        "Incorrect white knights number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4knnn/nnnnnnnn/8/8/8/8/3PPP2/4K3 w - - 0 1"}};
        },
        "Incorrect black knights number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/7P/PPPPPPPP/4K3 w - - 0 1"}};
        },
        "Incorrect white pawns number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/pppppppp/p7/8/8/8/3PPP2/4K3 w - - 0 1"}};
        },
        "Incorrect black pawns number."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"rnbqkbnr/pppppppp/8/8/8/7P/PPPPPPPP/RNBQKBNR w - - 0 1"}};
        },
        "White pieces count greater than 16."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"rnbqkbnr/pppppppp/p7/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1"}};
        },
        "Black pieces count greater than 16."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"8/8/8/4k3/3K4/8/8/8 w - - 0 1"}};
        },
        "Kingns threat each other."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"8/8/8/4k3/3K4/8/8/8 b - - 0 1"}};
        },
        "Kingns threat each other."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/8/8/8/8/8/4R3/4K3 w - - 0 1"}};
        },
        "Inactive king was threated."
    );

    assert_error_was_thrown(
        [](){
            Handler{FEN{"4k3/4r3/8/8/8/8/8/4K3 b - - 0 1"}};
        },
        "Inactive king was threated."
    );
}
