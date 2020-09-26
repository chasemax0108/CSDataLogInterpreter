#include "Parser.h"
#include "TokenType.h"
#include <iostream>

using namespace std;

// IF IT HITS A TERMINAL, ADVANCE THE CURRENT TOKEN

void Parser::Parse(vector<Token> &inputTokens, DataLogProgram* program) {
	workingTokens = inputTokens;
	currentToken = 0;
	ParseDataLogProgram(program);
	program->updateDomain();
}

void Parser::ParseParameter(Predicate* parentPred, Parameter* p, Expression* e) {
	TokenType current = workingTokens[currentToken].getType();
	if (current == STRING || current == ID) { // FIRST set
		if (parentPred != nullptr) { // If the function has received a parentPred, then we can insert it (1st iter)
			parentPred->addParam(new PlainParameter(workingTokens[currentToken].getValue()));
		}
		else { // we are looking for the sub-field of an expression
			p->setValue(workingTokens[currentToken].getValue());
		}
		currentToken++;
		return;
	}
	else if (current == LEFT_PAREN) {
		if (parentPred != nullptr) { //If the function has received a parentPred, then we can insert it (1st iter)
			Expression* newExp = new Expression();
			parentPred->addParam(newExp);
			ParseExpression(newExp);
		}
		else { // we are looking for the sub-field of an expression
			ParseExpression(e);
		}
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseOperator(Expression* e) {
	TokenType current = workingTokens[currentToken].getType();
	if (current == ADD || current == MULTIPLY) {
		e->setOperator(current);
		currentToken++;
		return;
	}
	else {
		throw workingTokens[currentToken];
	}
}

void Parser::ParseExpression(Expression* parentExp) {
	if (workingTokens[currentToken].getType() == LEFT_PAREN) { // FIRST Set
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) { // special case for data structure; if expression
			Expression* newExp = new Expression();
			parentExp->setParam1(newExp);
			ParseParameter(nullptr, nullptr, newExp);
		}
		else {
			ParseParameter(nullptr, parentExp->getParam1(), nullptr);
		}
		ParseOperator(parentExp);
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			Expression* newExp = new Expression();
			parentExp->setParam2(newExp);
			ParseParameter(nullptr, nullptr, newExp);
		}
		else {
			ParseParameter(nullptr, parentExp->getParam2(), nullptr);
		}
		if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
			currentToken++;
			return;
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseStringList(Predicate* p) {
	if (workingTokens[currentToken].getType() == COMMA) { // FIRST set
		currentToken++;
		if (workingTokens[currentToken].getType() == STRING) {
			p->addParam(new PlainParameter(workingTokens[currentToken].getValue()));
			currentToken++;
			ParseStringList(p);
			return;
		}
	}
	else if (workingTokens[currentToken].getType() == RIGHT_PAREN) { // FOLLOW set
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseIDList(Predicate* p) {
	if (workingTokens[currentToken].getType() == COMMA) { // FIRST set
		currentToken++;
		if (workingTokens[currentToken].getType() == ID) {
			p->addParam(new PlainParameter(workingTokens[currentToken].getValue()));
			currentToken++;
			ParseIDList(p);
			return;
		}
	}
	else if (workingTokens[currentToken].getType() == RIGHT_PAREN) { // FOLLOW set
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseParameterList(Predicate* p) {
	if (workingTokens[currentToken].getType() == COMMA) { // FIRST
		currentToken++;
		ParseParameter(p, nullptr, nullptr);
		ParseParameterList(p);
		return;
	}
	else if (workingTokens[currentToken].getType() == RIGHT_PAREN) { // FOLLOW set
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParsePredicate(Rule* r, Predicate* p) {
	if (workingTokens[currentToken].getType() == ID) {
		Predicate* newPred;
		if (r != nullptr) {
			newPred = new Predicate(workingTokens[currentToken].getValue());
			r->addPred(newPred);
		}
		else {
			newPred = p;
		}
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			currentToken++;
			ParseParameter(newPred, nullptr, nullptr);
			ParseParameterList(newPred);
			if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
				currentToken++;
				return;
			}
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParsePredicateList(Rule* r) {
	if (workingTokens[currentToken].getType() == COMMA) { // First
		currentToken++;
		ParsePredicate(r, nullptr);
		ParsePredicateList(r);
		return;
	}
	else if (workingTokens[currentToken].getType() == PERIOD) { // Follow
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseHeadPredicate(Rule* r) {
	if (workingTokens[currentToken].getType() == ID) {
		Predicate* newHeadPred = new Predicate(workingTokens[currentToken].getValue());
		r->addHeadPred(newHeadPred);
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			currentToken++;
			if (workingTokens[currentToken].getType() == ID) {
				newHeadPred->addParam(new PlainParameter(workingTokens[currentToken].getValue()));
				currentToken++;
				ParseIDList(newHeadPred);
				if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
					currentToken++;
					return;
				}
			}
		}
		//delete newHeadPred;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseScheme(DataLogProgram* p) {
	Predicate* newScheme = new Predicate();
	p->addScheme(newScheme);
	if (workingTokens[currentToken].getType() == ID) {
		newScheme->setid(workingTokens[currentToken].getValue());
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			currentToken++;
			if (workingTokens[currentToken].getType() == ID) {
				newScheme->addParam(new PlainParameter(workingTokens[currentToken].getValue()));
				currentToken++;
				ParseIDList(newScheme);
				if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
					currentToken++;
					return;
				}
			}
		}
	}
	//delete newScheme;
	throw workingTokens[currentToken];
}

void Parser::ParseFact(DataLogProgram* p) {
	if (workingTokens[currentToken].getType() == ID) {
		Predicate* newPred = new Predicate(workingTokens[currentToken].getValue());
		p->addFact(newPred);
		currentToken++;
		if (workingTokens[currentToken].getType() == LEFT_PAREN) {
			currentToken++;
			if (workingTokens[currentToken].getType() == STRING) {
				newPred->addParam(new PlainParameter(workingTokens[currentToken].getValue()));
				currentToken++;
				ParseStringList(newPred);
				if (workingTokens[currentToken].getType() == RIGHT_PAREN) {
					currentToken++;
					if (workingTokens[currentToken].getType() == PERIOD) {
						currentToken++;
						return;
					}
				}
			}
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseRule(DataLogProgram* p) {
	if (workingTokens[currentToken].getType() == ID) {
		Rule* newRule = new Rule();
		p->addRule(newRule);
		ParseHeadPredicate(newRule);
		if (workingTokens[currentToken].getType() == COLON_DASH) {
			currentToken++;
			ParsePredicate(newRule, nullptr);
			ParsePredicateList(newRule);
			if (workingTokens[currentToken].getType() == PERIOD) {
				currentToken++;
				return;
			}
		}
		//delete newRule;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseQuery(DataLogProgram* p) {
	if (workingTokens[currentToken].getType() == ID) {
		Predicate* newPred = new Predicate();
		p->addQuery(newPred);
		ParsePredicate(nullptr, newPred);
		if (workingTokens[currentToken].getType() == Q_MARK) {
			currentToken++;
			return;
		}
	}
	throw workingTokens[currentToken];
}

void Parser::ParseSchemeList(DataLogProgram* p) {
	if (workingTokens[currentToken].getType() == ID) {
		ParseScheme(p);
		ParseSchemeList(p);
		return;
	}
	else if (workingTokens[currentToken].getType() == FACTS) {
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseFactList(DataLogProgram* p) {
	if (workingTokens[currentToken].getType() == ID) {
		ParseFact(p);
		ParseFactList(p);
		return;
	}
	else if (workingTokens[currentToken].getType() == RULES) {
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseRuleList(DataLogProgram* p) {
	if (workingTokens[currentToken].getType() == ID) {
		ParseRule(p);
		ParseRuleList(p);
		return;
	}
	else if (workingTokens[currentToken].getType() == QUERIES) {
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseQueryList(DataLogProgram* p) {
	if (workingTokens[currentToken].getType() == ID) {
		ParseQuery(p);
		ParseQueryList(p);
		return;
	}
	else if (workingTokens[currentToken].getType() == ENDOFFILE) {
		return;
	}
	throw workingTokens[currentToken];
}

void Parser::ParseDataLogProgram(DataLogProgram* p) {
	if (workingTokens[currentToken].getType() == SCHEMES) {
		currentToken++;
		if (workingTokens[currentToken].getType() == COLON) {
			currentToken++;
			ParseScheme(p);
			ParseSchemeList(p);
			if (workingTokens[currentToken].getType() == FACTS) {
				currentToken++;
				if (workingTokens[currentToken].getType() == COLON) {
					currentToken++;
					ParseFactList(p);
					if (workingTokens[currentToken].getType() == RULES) {
						currentToken++;
						if (workingTokens[currentToken].getType() == COLON) {
							currentToken++;
							ParseRuleList(p);
							if (workingTokens[currentToken].getType() == QUERIES) {
								currentToken++;
								if (workingTokens[currentToken].getType() == COLON) {
									currentToken++;
									ParseQuery(p);
									ParseQueryList(p);
									if (workingTokens[currentToken].getType() == ENDOFFILE) {
										return;
									}
								}
							}
						}

					}
				}
			}
		}
	}
	throw workingTokens[currentToken];
}