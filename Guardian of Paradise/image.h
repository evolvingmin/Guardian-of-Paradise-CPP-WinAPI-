#pragma once
#include "animation.h"
//=====================================================
// 2015.03.11 ## image Class ## - Thursday Of Blood
//=====================================================
#include "animation.h"

class image
{
public:
	//�̹��� �ε� ��Ÿ��
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ��κ��� ����
		LOAD_FILE,			//���Ϸκ��� ����
		LOAD_EMPTY,			//�׳� ����
		LOAD_END			//�ƹ��͵� ����
	};

	//�̹��� ���� ����ü
	typedef struct tagImageInfo
	{
		DWORD	resID;			//���ҽ�ID
		HDC		hMemDC;			//�޸�DC
		HBITMAP	hBit;			//��Ʈ��
		HBITMAP	hOBit;			//�õ��Ʈ��
		float	x;				//�̹��� x��ǥ
		float	y;				//�̹��� y��ǥ
		int		width;			//����ũ��
		int		height;			//����ũ��
		int		currentFrameX;	//���� ������ X
		int		currentFrameY;	//���� ������ Y
		int		maxFrameX;		//�ִ� ������ X
		int		maxFrameY;		//�ִ� ������ Y
		int		frameWidth;		//������ ����ũ��
		int		frameHeight;	//������ ����ũ��
		BYTE	loadType;		//�̹����ε�Ÿ��
		RECT	boundingBox;	//�̹��� �ٿ���ڽ�

		//�ʱ�ȭ
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			boundingBox = RectMake(0, 0, 0, 0);
		}

	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	//�����ڿ��� ����̴ϼ� ������� �ٷ� �ʱ�ȭ ���ٰ�!!
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�̹��� �̸�

	BOOL			_trans;			//��������̳�? 
	COLORREF		_transColor;	//�����÷� Ű

	BLENDFUNCTION	_blendFunc;		//���ĺ����带 ���� ����
	LPIMAGE_INFO	_blendImage;	//���ĺ����带 ����ϱ� ���� �̹��� ����

public:
	image(void);
	~image(void);

	image(image&& other)
	{
		_imageInfo = other._imageInfo;
		_fileName = other._fileName;
		_trans = other._trans;
		_transColor = other._transColor;
		_blendFunc = other._blendFunc;
		_blendImage = other._blendImage;

		other._imageInfo = nullptr;
		other._fileName = nullptr;
		other._trans = false;
		other._transColor = 255;

		other._blendImage = nullptr;
	}
	image& operator=(image&& other)
	{
		if (this != &other)
		{
			this->_imageInfo = other._imageInfo;
			this->_fileName = other._fileName;
			this->_trans = other._trans;
			this->_transColor = other._transColor;
			this->_blendFunc = other._blendFunc;
			this->_blendImage = other._blendImage;

			other._imageInfo = nullptr;
			other._fileName = nullptr;
			other._trans = false;
			other._transColor = 255;
			other._blendImage = nullptr;
		}
		return *this;
	}

	//�ʱ�ȭ �Լ�
	//�� ��Ʈ�� �̹��� �����
	HRESULT init(int width, int height);

	//�̹����� ���ҽ��κ��� �о�´�
	HRESULT	init(const DWORD resID, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);

	//�̳��� �� �߿���
	//�̹��� ���� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�̹��� + ������ ���� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//����
	void release(void);

	//���� Ű ����
	void setTransColor(BOOL trans, COLORREF transColor);

	//==================================================================
	//		## �Ϲݷ��� ##
	//==================================================================
	//����(hdc) 0, 0 ��ġ�� �̹����� �Ѹ���
	void render(HDC hdc);
	//����(hdc, x��ǥ, y��ǥ) ���� ���ϴ� ������ġ�� �̹����� �Ѹ���
	void render(HDC hdc, int destX, int destY);
	//����(hdc, x��ǥ, y��ǥ, �����̹��� x��ǥ, �����̹��� x��ǥ, �����̹��� ����ũ��, �����̹��� ����ũ��)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//==================================================================
	//		## �����ӷ��� ##
	//==================================================================

	//�����ӷ���(hdc, x��ǥ, y��ǥ) ���� ���ϴ� ������ġ�� �������̹����� �Ѹ���
	void frameRender(HDC hdc, int destX, int destY);
	//�����ӷ���(hdc, x��ǥ, y��ǥ, ������������ X��ġ, ������������ Y��ġ)
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//==================================================================
	//		## ���ķ��� ##
	//==================================================================

	//���ķ���(hdc, ���İ�) 0, 0 ��ġ�� �̹����� �Ѹ���
	void alphaRender(HDC hdc, BYTE alpha);
	//���ķ���(hdc, x��ǥ, y��ǥ, ���İ�) ���� ���ϴ� ������ġ�� �̹����� �Ѹ���
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	//���ķ���(hdc, x��ǥ, y��ǥ, �����̹��� x��ǥ, �����̹��� x��ǥ, �����̹��� ����ũ��, �����̹��� ����ũ��, ���İ�)
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//==================================================================
	//		## ������ ���ķ��� ##
	//==================================================================

	//������ ���ķ���(hdc, x��ǥ, y��ǥ, ������������ X��ġ, ������������ Y��ġ, ���İ�)
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//==================================================================
	//		## �������� ## (��׶��� �� ��ũ�Ѹ�)
	//==================================================================

	//��������(hdc, ������ų ��Ʈ����, x������, y������)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//==================================================================
	//		## �ִϷ��� + �ִϷ������� ##
	//==================================================================

	//�ִϷ���(hdc, x��ǥ, y��ǥ, �ִϸ��̼�)
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	//�ִϷ�������(hdc, x��ǥ, y��ǥ, �ִϸ��̼�, ���İ�)
	void aniRenderAlpha(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//==================================================================
	//		## �̹��� ���� inline(��ũ���Լ�) ##
	//==================================================================

	//DC ��´�
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//�̹��� x��ǥ ����
	inline void setX(float x) { _imageInfo->x = x; }

	//�̹��� x��ǥ ���
	inline float getX(void) { return _imageInfo->x; }

	//�̹��� y��ǥ ����
	inline void setY(float y) { _imageInfo->y = y; }

	//�̹��� y��ǥ ����
	inline float getY(void) { return _imageInfo->y; }

	//�̹��� ������ǥ ����
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//����ũ�� ���
	inline int getWidth(void) { return _imageInfo->width; }

	//����ũ�� ���
	inline int getHeight(void) { return _imageInfo->height; }

	//�ٿ���ڽ�(�浹üũ)
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_imageInfo->x - (_imageInfo->width / 2)),
			int(_imageInfo->y - (_imageInfo->height / 2)),
			int(_imageInfo->x + (_imageInfo->width / 2)),
			int(_imageInfo->y + (_imageInfo->height / 2)) };
		return rc;
	}

	//�����ӹٿ�� �ڽ�(�浹üũ)
	inline RECT frameBoundingBox(void)
	{
		RECT rc = { int(_imageInfo->x),
			int(_imageInfo->y),
			int(_imageInfo->x + _imageInfo->frameWidth),
			int(_imageInfo->y + _imageInfo->frameHeight) };
		return rc;
	}

	//������X ����
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	//������Y ����
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	//������X ���
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }

	//������Y ���
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	//������ ���α��� ���
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }

	//������ ���α��� ���
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//�ƽ������� x ���
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }

	//�ƽ������� y ���
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }
};
