#include "ast.hpp"

std::list <Group> GroupList;

Node::~Node() {};

Group::Group(const NodePtr &_name, const NodePtr newChildren)
{
  if(_name) name = word(_name);
  this->children.push_back(newChildren);
  GroupList.push_back(this);
}

GroupMember::GroupMember(const NodePtr &_name, const NodePtr newChildren)
{
  name = word(_name);
  this->children.push_back(newChildren);
}
GroupMember::GroupMember(std::string _name)
  {
    std::cout << _name;
    name = _name;
  }

void GroupMember::print(std::ostream &out) const
{
  if(name != "end")
  {
    std::cout <<  name <<children.at(0);
  }
}

int GroupMember::type() const {
  return GROUP_MEMBER;
}

int Group::type() const{
  return GROUP;
}
void Group::print(std::ostream &out) const {
  out  << children.at(0) << std::endl;
}
void GroupMember::print(std::ostream &out, std::list<Feature> IntFeatures, std::list<Feature> StringFeatures,
  std::list<IntValue> IntValues, std::list<StringValue> StringValues) const{
    std::cout << name << std::endl;
  std::list<Feature>::const_iterator intF = IntFeatures.begin();
  std::list<Feature>::const_iterator stringF = StringFeatures.begin();
  std::list<IntValue>::const_iterator intV = IntValues.begin();
  std::list<StringValue>::const_iterator stringV = StringValues.begin();
  for(; intF != IntFeatures.end() && intV != IntValues.end();){
    intF->print(out);
    out << ": ";
    intV->print(out);
    out << ";\n";
    intF++;
    intV++;
  }
  for(; stringF != StringFeatures.end() && stringV != StringValues.end();){
    stringF->print(out);
    out << ": ";
    stringV->print(out);
    out << ";\n";
    stringF++;
    stringV++;
  }
}

void StringValue::print(std::ostream &out) const{
  out << value;
}
void IntValue::print(std::ostream &out) const{
  out << name;
}
void Feature::print(std::ostream &out) const{
  out << name;
}
WordNode::WordNode(const std::string &_word)
{
  word = _word;
}

int WordNode::type() const
{
  return WORD_LITERAL;
}

void WordNode::print(std::ostream &out) const {
  out << word;
}

NumberNode::NumberNode(int _number)
{
  number = _number;
}

int NumberNode::type() const
{
  return NUMBER_LITERAL;
}

void NumberNode::print(std::ostream &out) const {
  out << "number(" << number << ")";
}


StartCommandNode::StartCommandNode(const NodePtr &target,
                                   const NodePtr &power)
{
  children.push_back(target);
  children.push_back(power);
}

int StartCommandNode::type() const { return START_COMMAND; }
void StartCommandNode::print(std::ostream &out) const {
  out << "start(target=" << children.at(0)
      << ", power=" << children.at(1) << ")";
}

const std::string & StartCommandNode::target() const
{
  return std::dynamic_pointer_cast<WordNode>(children.at(0))->word;
}

int StartCommandNode::power() const
{
  return std::dynamic_pointer_cast<NumberNode>(children.at(1))->number;
}

StopCommandNode::StopCommandNode(const NodePtr &target) {
  children.push_back(target);
}

int StopCommandNode::type() const { return STOP_COMMAND; }
void StopCommandNode::print(std::ostream &out) const {
  out << "stop(target=" << children.at(0) << ")";
}

const std::string & StopCommandNode::target() const {
  return std::dynamic_pointer_cast<WordNode>(children.at(0))->word;
}

int ProgramNode::type() const { return PROGRAM; }

void ProgramNode::print(std::ostream &out) const {
  out << "program(children=[" << std::endl;
  for (size_t i=0; i<children.size(); ++i) {
    out << "  " << children[i] << " // child " << i << std::endl;
  }
  out << "]) // program" << std::endl;
}

int number(const NodePtr &p) {
  return std::dynamic_pointer_cast < NumberNode >(p)->number;
}

const std::string & word(const NodePtr &p) {

  if (p) return std::dynamic_pointer_cast < WordNode >(p)->word;
  else return NULL;

}

NodePtr node(int number) {
  return NodePtr(new NumberNode(number));
}

NodePtr node(const std::string &word) {
  std::cout << word;
  return NodePtr(new WordNode(word));
}

std::ostream &operator<< (std::ostream& out, const NodePtr &p) {
  p->print(out);
  return out;
}
