#pragma once
#include<list>
#include<string>
#include<memory>
#include<filesystem>

class Node
{
public:
	using size_t = std::uintmax_t;
	using node_ptr_t = std::shared_ptr<Node>;
	using children_t = std::list<node_ptr_t>;

public:
	Node(std::string name);

	const std::string& GetName() const;

	void SetSize(size_t size);
	Node::size_t GetSize() const;

	void AddChild(const node_ptr_t& childPtr);
	void AddChild(node_ptr_t&& childPtr);

	const Node::children_t& GetChildren() const;

private:
	std::string m_name;
	size_t m_size;
	children_t m_children;
};

class DirectoryChecker
{
public:
	DirectoryChecker(std::filesystem::path base);

	bool BeginCheck();

	const std::filesystem::path& GetBasePath() const;
	const Node::node_ptr_t& GetRootNode() const;

private:
	Node::node_ptr_t  _CheckSubPath(const std::filesystem::path& subPath);
	
private:
	Node::node_ptr_t m_root;
	std::filesystem::path m_basePath;
};