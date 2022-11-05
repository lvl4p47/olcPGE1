#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class P1 : public olc::PixelGameEngine
{
public:
	P1()
	{
		sAppName = "Example";
	}

	olc::Sprite* out = nullptr;
	olc::Sprite* hex = nullptr;
	olc::Decal* ht = nullptr;

private:
	struct Hex
	{
		unsigned char n;
	};

	unsigned char ArrWidth = 100;
	unsigned char ArrHeight = 100;
	Hex* arr = nullptr;

public:
	bool OnUserCreate() override
	{
		hex = new olc::Sprite("textures/Hex.png");
		out = new olc::Sprite("textures/Out.png");
		ht = new olc::Decal(hex);

		arr = new Hex[ArrWidth * ArrHeight];
		memset(arr, 0, ArrWidth * ArrHeight * sizeof(Hex));

		CreateArr();
		DrawArr();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		
		if (GetMouse(0).bHeld || GetMouse(1).bHeld)
		{
			int mx, my;
			my = floor((GetMouseY() - 1) / 7);
			mx = ((GetMouseX() + 4 * my) / 8) - ArrHeight / 2;
			if (mx < 0 || my < 0 || mx > ArrWidth - 1 || my > ArrHeight - 1)
				std::cout << mx << "\t" << my << "\n";
			else
			{
				if (GetMouse(0).bHeld && !GetMouse(1).bHeld)
					arr[my * ArrWidth + mx].n = 1;
				else if (!GetMouse(0).bHeld && GetMouse(1).bHeld)
					arr[my * ArrWidth + mx].n = 0;
				DrawHex(mx, my, arr[my * ArrWidth + mx].n, 255, 1);
			}
			
		}
		if (GetKey(olc::Key::R).bReleased)
		{
			memset(arr, 0, ArrWidth * ArrHeight * sizeof(Hex));
			DrawArr();
		}
		return true;
	}

	void CreateArr()
	{
		for (int x = 0; x < ArrWidth; x++)
			for (int y = 0; y < ArrHeight; y++)
			{
				arr[y * ArrWidth + x].n = 0;
			}
	}

	void DrawArr()
	{
		for (int y = 0; y < ArrHeight; y++)
			for (int x = 0; x < ArrWidth; x++)
				DrawHex(x, y, arr[y * ArrWidth + x].n, 255, 1);
	}

	void DrawHex(int arrx, int arry, int n, int a, bool f)
	{
		int y = arry * 7;
		int x = arrx * 8 + (ArrHeight - arry) * 4;

		bool t[72] = {
			0,0,0,1,1,0,0,0,
			0,1,1,f,f,1,1,0,
			1,f,f,f,f,f,f,1,
			1,f,f,f,f,f,f,1,
			1,f,f,f,f,f,f,1,
			1,f,f,f,f,f,f,1,
			1,f,f,f,f,f,f,1,
			0,1,1,f,f,1,1,0,
			0,0,0,1,1,0,0,0,
		};

		int r, g, b;
		switch (n)
		{
		case 0:
			r = 168;
			g = 249;
			b = 255;
			break;
		case 1:
			r = 62;
			g = 146;
			b = 204;
			break;
		}

		for (int y1 = 0; y1 < 9; y1++)
			for (int x1 = 0; x1 < 8; x1++)
			{
				if (t[y1 * 8 + x1])
					Draw(x + x1, y + y1, olc::Pixel(r, g, b, a));
			}
	}
};

int main()
{
	P1 ca;
	if (ca.Construct(1200, 710, 1, 1))
		ca.Start();
	return 0;
}