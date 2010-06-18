#include <dds/condition.hpp>


/////////////////////////////////////////////////////////////////////////////
dds::Condition::Condition(dds::peer::ConditionImpl* aci) :
	cond_(aci) {
}
dds::Condition::~Condition() {
}


bool
dds::Condition::operator==(const dds::Condition& other)
{
	return cond_ == other.cond_;
}

/////////////////////////////////////////////////////////////////////////////
dds::ReadCondition::ReadCondition(dds::peer::ReadConditionImpl* arc)
: Condition(arc), pcond_(arc)
{ }

dds::ReadCondition::ReadCondition()
: Condition(0), pcond_(0)
{

}

dds::ReadCondition::~ReadCondition() {
}


/////////////////////////////////////////////////////////////////////////////
dds::QueryCondition::QueryCondition(dds::peer::QueryConditionImpl* qcond)
	: ReadCondition(qcond), pcond_(qcond)
	{ }

dds::QueryCondition::QueryCondition()
	: ReadCondition(0), pcond_(0)
	{ }

dds::QueryCondition::~QueryCondition() {
}
