
#include "../../src/ax_libs.hpp"
#include "../../src/lambda_transition_deletion.hpp"

#include "../main_test.hpp"

TEST_CASE( "Testing transitive closure of lambda transitions" )
{
    auto lambda = machines::lambda_symbol;

    SECTION( "Test on machine 1" )
    {
        constexpr size_t n = 5;
        constexpr size_t m = 10;
        auto machine = machines::finite_state_machine( 5, 9 );

        ax::matrix<int> transitions = {

        };

        ax::matrix<int> closure = {

        };

        SECTION( "Check matrix sizes" ) {
            REQUIRE( closure.row_count() == n );
            REQUIRE( closure.col_count() == n );

            REQUIRE( transitions.row_count() == n );
            REQUIRE( transitions.col_count() == n );
        }

        for( size_t r = 0; r < transitions.row_count(); ++r )
            for( size_t c = 0; c < transitions.col_count(); ++c )
                if( transition( r, c ) )
                    machine.add_rule( r, lambda, c );

        auto result = algs::transitive_closure_of_lambda_transitions( machine );

        ax::matrix<int> result_matrix = (
            transitions.row_count(),
            transitions.col_count(),
            []( auto r, auto c )
            {
                return (result[r][c]) ? 1 : 0;
            }
        )

        REQUIRE( closure == result_matrix );
    }
}
