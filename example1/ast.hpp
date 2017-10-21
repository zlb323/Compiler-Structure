#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <list>

class Node {
public: enum {
    PROGRAM,
    START_COMMAND,
    STOP_COMMAND,
    WORD_LITERAL,
    NUMBER_LITERAL,
    GROUP,
    GROUP_MEMBER,
    COMMAND,
    VARIABLE,
    FEATURE,
    STRING_VALUE,
    INT_VALUE,
    DASH,
    NAME
  };
public: std::vector < std::shared_ptr < Node > > children;
public: virtual int type() const = 0;
public: virtual void print(std::ostream &out) const = 0;
public: virtual ~Node();
};

typedef std::shared_ptr < Node > NodePtr;

class WordNode : public Node {
public: WordNode &operator= (std::shared_ptr<Node> input);
public: std::string word;
public: WordNode(const std::string &_word);
public: int type() const;
public: void print(std::ostream &out) const;
};

class Feature{
public: std::string name;
public: Feature(std::string &_name);
public: int type() const;
public: void print(std::ostream &out) const;
public: Feature();
};
typedef std::shared_ptr < Feature > FeaturePtr;

class Command{
public: std::string command;
public: Command(std::string &_command);
public: int type() const;
public: void print(std::ostream &out) const;
public: virtual ~Command();
};
typedef std::shared_ptr < Command > CommandPtr;


class Variable{
public: std::string name;
public: Variable(std::string &_name);
public: int type() const;
public: void print(std::ostream &out) const;
};
typedef std::shared_ptr < Variable > VariablePtr;


class StringValue {
public: std::string value;
public: StringValue(std::string &_name);
public: int type() const;
public: void print(std::ostream &out) const;
};
typedef std::shared_ptr < StringValue > StringValuePtr;


class IntValue{
public: std::string name;
public: IntValue(std::string &_name);
public: int type() const;
public: void print(std::ostream &out) const;
};
typedef std::shared_ptr < IntValue > IntValuePtr;

typedef std::shared_ptr < WordNode > WordNodePtr;

class GroupMember : public Node{
public: std::string name;
public: GroupMember(const NodePtr &name, const NodePtr newChildren);
public: GroupMember(std::string name);
public: int type() const;
public: void print(std::ostream &out) const;
public: void print(std::ostream &out, std::list<Feature>, std::list<Feature>,
  std::list<IntValue>, std::list<StringValue>) const;
};

typedef std::shared_ptr < GroupMember > GroupMemberPtr;
class Group : public Node{
public: std::string name;
public: std::list<Feature> StringFeatures;
public: std::list<StringValue> StringValues;
public: std::list<Feature> IntFeatures;
public: std::list<IntValue> IntValues;
public: int NumInts;
public: int NumStrings;
public: Group(const NodePtr &name, const NodePtr newChildren);
public: int type() const;
public: void print(std::ostream &out) const;
};
typedef std::shared_ptr < Group > GroupPtr;

class NumberNode : public Node {
public: int number;
public: NumberNode(int _number);
public: int type() const;
public: void print(std::ostream &out) const;
};

typedef std::shared_ptr < NumberNode > NumberNodePtr;


class StartCommandNode : public Node {
public: StartCommandNode(const NodePtr &target, const NodePtr &power);
public: int type() const;
public: void print(std::ostream &out) const;

public: const std::string & target() const;

public: int power() const;

};

typedef std::shared_ptr < StartCommandNode > StartCommandNodePtr;

class StopCommandNode : public Node {
public: StopCommandNode(const NodePtr &target);
public: int type() const;
public: void print(std::ostream &out) const;

public: const std::string & target() const;

};

typedef std::shared_ptr < StopCommandNode > StopCommandNodePtr;

class ProgramNode : public Node {
public: int type() const;
public: void print(std::ostream &out) const;
};

typedef std::shared_ptr < ProgramNode > ProgramNodePtr;

int number(const NodePtr &p);

const std::string & word(const NodePtr &p);

NodePtr node(int number);

NodePtr node(const std::string &word);

std::ostream &operator<< (std::ostream& out, const NodePtr &p);
