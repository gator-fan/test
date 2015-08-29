#ifndef _STRATEGY_H_
#define _STRATEGY_H_
class Strategy{
	public:
		Strategy();
		virtual ~Strategy();
		virtual void AlgorithmInteraface() = 0;
};

class ConcreteStrategyA:public Strategy{
	public:
		ConcreteStrategyA();
		virtual ~ConcreteStrategyA();
		void AlgorithmInterface();
};

class ConcreteStrategyB:public Strategy{
	public:
		ConcreteStrategyB();
		virtual ~ConcreteStrategyB();
		void AlgorithmInterface();
};
#endif
