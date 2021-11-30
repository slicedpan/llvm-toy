#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "../src/value.hpp"

using namespace LLVMToy;
using namespace Catch::Matchers;

TEST_CASE( "String Values are created correctly", "[Value]" ) {

  Value short_str = Value::make_string("fooba");  

  REQUIRE( short_str.get_type() == ValueType::ShortString );
  REQUIRE_THAT( short_str.to_string(), Equals("fooba") );

  Value long_str = Value::make_string("foobar");

  REQUIRE( long_str.get_type() == ValueType::String );
  REQUIRE_THAT( long_str.to_string(), Equals("foobar") );
  REQUIRE_THAT( (char*)long_str.pointer_value(), Equals("foobar") );
}

TEST_CASE( "Numeric Values are created correctly", "[Value]" ) {
  Value num = Value::make_number(3.4);
  Value nan = Value::make_number(0.0 / 0.0);

  REQUIRE( num.get_type() == ValueType::FloatingPoint );
  REQUIRE( nan.get_type() == ValueType::FloatingPoint );
}

TEST_CASE( "Generic pointers are created correctly", "[Value]" ) {
  int int_values[4] = {1,2,3,4};
  Value ptr_wrapper = Value::make_generic_ptr((void*)&int_values[2]);

  REQUIRE( ptr_wrapper.get_type() == ValueType::GenericPointer );
  REQUIRE( *(int*)ptr_wrapper.pointer_value() == 3 );

  Value unaligned_ptr = Value::make_generic_ptr((void*)&int_values[1]);
  REQUIRE( *(int*)unaligned_ptr.pointer_value() != 2 );
}

TEST_CASE( "Constant Values are created correctly", "[Value]" ) {
  Value true_val = Value::make_true();
  Value false_val = Value::make_false();
  Value nil_val = Value::make_nil();
  Value undefined_val = Value::make_undefined();

  REQUIRE( true_val.get_type() == ValueType::Boolean );
  REQUIRE( true_val.is_truthy() == true );
  REQUIRE( false_val.get_type() == ValueType::Boolean );
  REQUIRE( false_val.is_truthy() == false );
  REQUIRE( nil_val.get_type() == ValueType::Nil );
  REQUIRE( nil_val.is_truthy() == false );
  REQUIRE( undefined_val.get_type() == ValueType::Undefined );
  REQUIRE( undefined_val.is_truthy() == false );
}