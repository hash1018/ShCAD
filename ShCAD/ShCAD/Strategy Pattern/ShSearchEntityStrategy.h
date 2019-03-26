

#ifndef _SHSEARCHENTITYSTRATEGY_H
#define _SHSEARCHENTITYSTRATEGY_H

class ShSearchEntityStrategy {
	friend class ShEntityTable;

protected:
	ShEntityTable *entityTable;
	double x;
	double y;
	double zoomRate;

public:
	ShSearchEntityStrategy(double x, double y, double zoomRate);
	virtual ~ShSearchEntityStrategy() = 0;

protected:
	virtual void Search() = 0;

private:
	//*** Not allowed to be created in heap area. stack only.
	void *operator new(size_t) {}
	//*** Not allowed to be created in heap area. stack only.
	void *operator new[](size_t) {}
};

class ShEntity;
class ShSearchEntityUniqueStrategy : public ShSearchEntityStrategy {

protected:
	ShEntity* *foundEntity;

public:
	ShSearchEntityUniqueStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate);
	~ShSearchEntityUniqueStrategy();

private:
	virtual void Search();


};

class ShSearchEntityCompositeChildIncludedStrategy : public ShSearchEntityStrategy {

protected:
	ShEntity* *foundEntity;

public:
	ShSearchEntityCompositeChildIncludedStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate);
	~ShSearchEntityCompositeChildIncludedStrategy();

private:
	virtual void Search();

};

#endif //_SHSEARCHENTITYSTRATEGY_H