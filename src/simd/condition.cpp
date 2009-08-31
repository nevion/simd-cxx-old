#include <simd/condition.hpp>

simd::ActiveConditionImpl::~ActiveConditionImpl() { }


simd::ActiveCondition::ActiveCondition(ActiveConditionImpl* aci) {
	this->reset(aci);
}
simd::ActiveCondition::~ActiveCondition() { }
