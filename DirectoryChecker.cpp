#include<iostream>
#include "DirectoryChecker.h"

Node::Node(std::string name):m_name(std::move(name)),m_size(0)
{
}

const std::string& Node::GetName() const
{
	return m_name;
}

void Node::SetSize(size_t size)
{
	m_size = size;
}

Node::size_t Node::GetSize() const
{
	return m_size;
}

void Node::AddChild(const node_ptr_t& childPtr)
{
	m_children.push_back(childPtr);
}

void Node::AddChild(node_ptr_t&& childPtr)
{
	m_children.push_back(childPtr);
}

const Node::children_t& Node::GetChildren() const
{
	return m_children;
}

DirectoryChecker::DirectoryChecker(std::filesystem::path base):m_basePath(std::move(base))
{
}

bool DirectoryChecker::BeginCheck()
{
	m_root = _CheckSubPath(m_basePath);

	return ( m_root != nullptr);
}

const std::filesystem::path& DirectoryChecker::GetBasePath() const
{
	return m_basePath;
}

const Node::node_ptr_t& DirectoryChecker::GetRootNode() const
{
	return m_root;
}

 Node::node_ptr_t DirectoryChecker::_CheckSubPath(const std::filesystem::path& subPath)
{
	 Node::node_ptr_t node = nullptr;

	 if (std::filesystem::is_regular_file(subPath))
	 {
		 node = std::make_shared<Node>(subPath.filename().string());
		 node->SetSize(std::filesystem::file_size(subPath));
	 }
	 else if (std::filesystem::is_directory(subPath))
	 {
		 Node::size_t dirSize = 0;
		 node = std::make_shared<Node>(subPath.filename().string());
		 for (const auto& subEntry : std::filesystem::directory_iterator(subPath))
		 {
			 try
			 {
				 auto childNodePtr = _CheckSubPath(subEntry.path());
				 if (childNodePtr != nullptr)
				 {
					 dirSize += childNodePtr->GetSize();
					 node->AddChild(std::move(childNodePtr));
				 }
			 }
			 catch (...)
			 {
			 }
		 }

		 node->SetSize(dirSize);
	 }

	 return node;
}


