#include <gtest/gtest.h>
#include <iostream>

#include <tengine/util/cfgparse/Serializer.hpp>
#include <tengine/util/cfgparse/Parser.hpp>
#include <tengine/util/cfgparse/CFGNode.hpp>

namespace{

bool diffNodes(const tengine::util::cfg::CFGNode& a, const tengine::util::cfg::CFGNode& b){

  if(a.nodeName != b.nodeName) return false;
  if(a.values != b.values) return false;
  if(a.children.size() != b.children.size()) return false;

  for(size_t i = 0; i < a.children.size(); i++){
    if(!diffNodes(a.children[i], b.children[i])) return false;
  }

  return true;

}

TEST(CFGSerializerTests, Loopback){
  tengine::util::cfg::CFGNode root;

  tengine::util::cfg::CFGNode child0;
  child0.nodeName = "child0";
  child0.values["stringfield"] = "Now darling, where do we go from here?";
  child0.values["intfield"] = "21";
  child0.values["boolfield"] = "false";

  tengine::util::cfg::CFGNode child1;
  child1.nodeName = "child1";
  child1.values["stringfield"] = "Hey honey, where do we go from here?";
  child1.values["intfield"] = "42";
  child1.values["boolfield"] = "true";

  child0.children.push_back(child1);
  root.children.push_back(child0);

  std::string serialized = tengine::util::cfg::CFGSerializer::serialize(root);
  std::cout << "\nSerialized output:\n"
            << serialized
            << "\n";

  std::vector<tengine::util::cfg::CFGNode> parsed = tengine::util::cfg::CFGParser::parse(serialized);

  ASSERT_EQ(parsed.size(), root.children.size());

  for(size_t i = 0; i < parsed.size(); i++){
    EXPECT_TRUE(diffNodes(parsed[i], root.children[i]));
  }

}

}