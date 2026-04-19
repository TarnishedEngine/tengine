#include <gtest/gtest.h>
#include <tengine/util/cfgparse/Parser.hpp>
#include <tengine/util/cfgparse/CFGNode.hpp>
#include <tengine/tengine_build_details.hpp>

TEST(CFGParserTests, SingleNodeParsing){

  std::string config = R"(

    SimpleNode{
      key = value
      int = 42
      float = 3.14
      boolean = true
    }

  )";

  auto nodes = tengine::util::cfg::CFGParser::parse(config);
  ASSERT_EQ(nodes.size(), 1);
  EXPECT_EQ(nodes[0].nodeName, "SimpleNode");
  EXPECT_EQ(nodes[0].getStringValue("key"), "value");
  EXPECT_EQ(nodes[0].getInteger("int"), 42);
  EXPECT_NEAR(nodes[0].getFloat("float"), 3.14, 1e-9);
  EXPECT_TRUE(nodes[0].getStringValue("boolean"));

}

TEST(CFGParserTestS, NestedNodeParsing){

  std::string config = R"(
        Parent {
            Child {
                GrandChild {
                    target = found
                }
            }
        }
    )";

  auto nodes = tengine::util::cfg::CFGParser::parse(config);

  ASSERT_EQ(nodes.size(), 1);
  ASSERT_EQ(nodes[0].children.size(), 1);
  ASSERT_EQ(nodes[0].children[0].children.size(), 1);

  auto& grandChild = nodes[0].children[0].children[0];
  EXPECT_EQ(grandChild.nodeName, "GrandChild");
  EXPECT_EQ(grandChild.getStringValue("target"), "found");

}

TEST(CFGParserTests, QuotesAndComments){

  std::string config = R"(
        // This is a top level comment
        FormattingNode {
            // Internal comment
            spaced_key = "Hello World"
            path = "//not/a/comment"
            pi = 3.14159 // inline comment
        }
    )";

  auto nodes = tengine::util::cfg::CFGParser::parse(config);

  ASSERT_EQ(nodes.size(), 1);
  EXPECT_EQ(nodes[0].getStringValue("spaced_key"), "Hello World");
  EXPECT_EQ(nodes[0].getStringValue("path"), "//not/a/comment");
  EXPECT_NEAR(nodes[0].getFloat("pi"), 3.14159, 0.0001);

}

TEST(CFGParserTests, MultipleTopLevelNodes){

  std::string config = R"(
        NodeA { id = 1 }
        NodeB { id = 2 }
    )";

  auto nodes = tengine::util::cfg::CFGParser::parse(config);

  ASSERT_EQ(nodes.size(), 2);
  EXPECT_EQ(nodes[0].nodeName, "NodeA");
  EXPECT_EQ(nodes[1].nodeName, "NodeB");
  EXPECT_EQ(nodes[0].getInteger("id"), 1);
  EXPECT_EQ(nodes[1].getInteger("id"), 2);

}