#pragma once
class Collider;

class BoxCollider : public Collider
{
public:
	BoxCollider();
	void SetRect (float _left, float _top, float _right, float _bottom);
	void SetRect(D2D1_POINT_2F center, D2D1_SIZE_F size);
	virtual ~BoxCollider();

public:

	bool IsCheckCrash(BoxCollider* _target);
	static BoxCollider* IsMovePossible(D2D1_POINT_2F point, D2D1_SIZE_F targetSize, float gravity);
	static BoxCollider* IsMovePossibleByLine(D2D1_POINT_2F point, D2D1_SIZE_F targetSize, float gravity);

	//virtual void Awake();
	virtual void Update();
	virtual void OnRender();
};