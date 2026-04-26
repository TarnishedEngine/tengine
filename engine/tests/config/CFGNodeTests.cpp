#include <gtest/gtest.h>

#include <tengine/tengine_build_details.hpp>
#include <tengine/util/cfgparse/CFGNode.hpp>

TEST(ConfigNodeTests, NodeParsesInt){

  tengine::build_details::printBuildDetails();

  tengine::util::cfg::CFGNode node;
  node.values["IntKey"] = "42";
  node.values["ErrorKey"] = "ErrorString";

  ASSERT_EQ(node.getInteger("IntKey"), 42);
  ASSERT_EQ(node.getInteger("ErrorKey", 21), 21);

}

TEST(ConfigNodeTests, NodeParsesFloat){

  tengine::build_details::printBuildDetails();

  tengine::util::cfg::CFGNode node;
  node.values["FloatKey"] = "3.14";
  node.values["ErrorKey"] = "ErrorString";

  ASSERT_NEAR(node.getFloat("FloatKey"), 3.14, 1e-9);
  ASSERT_EQ(node.getInteger("ErrorKey", 21), 21);

}

TEST(ConfigNodeTests, NodeParsesBool){

  tengine::build_details::printBuildDetails();

  tengine::util::cfg::CFGNode node;
  node.values["BoolKeyWord"] = "true";
  node.values["BoolKeyNumber"] = "1";
  node.values["ErrorKey"] = "ErrorString";

  ASSERT_EQ(node.getBoolean("BoolKeyWord"), true);
  ASSERT_EQ(node.getBoolean("BoolKeyNumber"), true);
  ASSERT_EQ(node.getInteger("ErrorKey", 21), 21);

}

TEST(ConfigNodeTests, NodeParsesString){

  tengine::build_details::printBuildDetails();

  tengine::util::cfg::CFGNode node;
  node.values["StringKey"] = "Hello, Tarnished!";

  ASSERT_EQ(node.getStringValue("StringKey"), "Hello, Tarnished!");

}

TEST(ConfigNodeTests, NodeReturnsNullOpt){

  tengine::build_details::printBuildDetails();

  tengine::util::cfg::CFGNode node;

  ASSERT_EQ(node.getStringValue("StringKey"), std::nullopt);

}