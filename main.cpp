#include<iostream>
#include "DirectoryChecker.h"


const Node::size_t KB = 1024;
const Node::size_t MB = 1024 * KB;
const Node::size_t GB = 1024 * MB;
const Node::size_t TB = 1024 * GB;

std::string FormatSize(Node::size_t size)
{
	std::string str;
	if (size > TB)
	{
		str = std::to_string(size / TB) + "TB";
	}
	else if (size > GB)
	{
		str = std::to_string(size / GB) + "GB";
	}
	else if (size > MB)
	{
		str = std::to_string(size / MB) + "MB";
	}
	else if (size > KB)
	{
		str = std::to_string(size / KB) + "KB";
	}
	else
	{
		str = std::to_string(size) + "B";
	}

	return str;
}

void OutputDirctoryNode(std::ostream& cout, const Node& node,const std::vector<int>& isLast)
{
	if (isLast.size() > 4)return;

	for (std::size_t index = 0;index + 1 < isLast.size();index++)
	{
		if (isLast[index])
		{
			cout << "     ";
		}
		else
		{
			cout << "©§    ";
		}
	}

	if (isLast.back())
	{
		cout << "©»©¥ ";
	}
	else
	{
		cout << "©Ç©¥ ";
	}

	cout << node.GetName() << "    [ " << FormatSize(node.GetSize())<<" ]" << std::endl;

	std::size_t index = 0;

	for (const auto& oneChild : node.GetChildren())
	{
		index++;
		if (oneChild == nullptr) continue;

		auto nextIsLast = isLast;
		if (index == node.GetChildren().size())
		{
			nextIsLast.push_back(1);
		}
		else
		{
			nextIsLast.push_back(0);
		}

		OutputDirctoryNode(cout, *oneChild, nextIsLast);
	}
}

std::ostream& operator<<(std::ostream& cout, const DirectoryChecker& dc)
{
	cout << dc.GetBasePath().string() << "    [ "<<FormatSize(dc.GetRootNode()->GetSize())<<" ]" << std::endl;

	if (dc.GetRootNode() == nullptr)
	{
		return cout;
	}

	std::size_t count = 0;
	for (const auto& oneChild : dc.GetRootNode()->GetChildren())
	{
		count++;
		if (oneChild == nullptr)
		{
			continue;
		}
		std::vector<int> isLast;
		if (count != dc.GetRootNode()->GetChildren().size())
		{
			isLast.push_back(0);
		}
		else
		{
			isLast.push_back(1);
		}
		OutputDirctoryNode(cout, *oneChild, isLast);
	}
	return cout;
}

int main(int argc, char** argv)
{
	std::filesystem::path basePath;
	if (argc < 2)
	{
		basePath = std::filesystem::current_path();
	}
	else
	{
		basePath = argv[1];
	}

	DirectoryChecker dc{basePath};
	if (!dc.BeginCheck())
	{
		std::cout << "Error!" << std::endl;
	}
	else
	{
		std::cout << dc<< std::endl;
	}

	return 0;
}