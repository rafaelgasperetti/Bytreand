#include <Compiler/MiddleEnd/SemanticTreeNode.h>

SemanticTreeNode::SemanticTreeNode(string name, FrontEndToken* relatedToken, int relatedTokenPositon, GrammarState* relatedState)
{
	SetName(name);
	SetGrammarState(relatedState);
	SetFrontEndToken(relatedToken, relatedTokenPositon);
}

void SemanticTreeNode::SetName(string name)
{
	Name = name;
}

string SemanticTreeNode::GetName()
{
	return Name;
}

void SemanticTreeNode::SetFrontEndToken(FrontEndToken* relatedToken, int relatedTokenPosition)
{
	if (relatedToken != NULL && relatedTokenPosition >= 0)
	{
		RelatedToken = relatedToken;
		RelatedTokenPosition = relatedTokenPosition;
	}
	else
	{
		throw invalid_argument("NULL related front end token is not allowed at \"" + GetName() + "\" (type: " + StringUtils::ToString(GetGrammarState()->GetType()) + ", position: " + StringUtils::ToString(GetRelatedTokenPosition()) + ") semantic tree node, as well as related token position lower than zero (current value: " + StringUtils::ToString(relatedTokenPosition) + ").");
	}
}

FrontEndToken* SemanticTreeNode::GetFrontEndToken()
{
	return RelatedToken;
}

int SemanticTreeNode::GetRelatedTokenPosition()
{
	return RelatedTokenPosition;
}

void SemanticTreeNode::SetGrammarState(GrammarState* relatedState)
{
	if (relatedState != NULL)
	{
		RelatedState = relatedState;
	}
	else
	{
		throw invalid_argument("NULL related state is not allowed at \"" + GetName() + "\" (type: " + StringUtils::ToString(GetGrammarState()->GetType()) + ", position: " + StringUtils::ToString(GetRelatedTokenPosition()) + ") semantic tree node.");
	}
}

GrammarState* SemanticTreeNode::GetGrammarState()
{
	return RelatedState;
}

void SemanticTreeNode::SetParentNode(SemanticTreeNode* parent)
{
	Parent = parent;
}

SemanticTreeNode* SemanticTreeNode::GetParentNode()
{
	return Parent;
}

void SemanticTreeNode::AddChild(SemanticTreeNode* child)
{
	if (child != NULL)
	{
		if (GetChild(child->GetName(), child->GetGrammarState()->GetType(), child->GetRelatedTokenPosition() == NULL))
		{
			Children->push_back(child);
		}
		else
		{
			throw invalid_argument("The duplicated child \"" + child->GetName() + "\" (type: " + StringUtils::ToString(child->GetGrammarState()->GetType()) + ", position: " + StringUtils::ToString(child->GetRelatedTokenPosition()) + ") is not allowed at \"" + GetName() + "\" (type: " + StringUtils::ToString(GetGrammarState()->GetType()) + ", position: " + StringUtils::ToString(GetRelatedTokenPosition()) + ") semantic tree node.");
		}
	}
	else
	{
		throw invalid_argument("NULL childs are not allowed at \"" + GetName() + "\" (type: " + StringUtils::ToString(GetGrammarState()->GetType()) +", position: " + StringUtils::ToString(GetRelatedTokenPosition()) + ") semantic tree node.");
	}
}

SemanticTreeNode* SemanticTreeNode::GetChild(string name, int stateType, int position)
{
	for (SemanticTreeNode* n : (*Children))
	{
		if (StringUtils::Equals(n->GetName(), name) && n->GetGrammarState()->GetType() == stateType && n->GetRelatedTokenPosition() == position)
		{
			return n;
		}
		else
		{
			return NULL;
		}
	}
}

vector<SemanticTreeNode*>* SemanticTreeNode::GetChildren()
{
	return Children;
}

bool SemanticTreeNode::IsLeafNode()
{
	return Children->size() == 0;
}