#enable_testing ()
add_test(NAME END_TO_END
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/test.sh 
            $<TARGET_FILE:rbt_main> 
			${CMAKE_CURRENT_SOURCE_DIR}/data
)