#include "eventTests.h"

TEST(Events, ResizeConstructor)
{
	Engine::WindowResizeEvent e_WR(800, 600);

	int32_t width1 = e_WR.getWidth();
	int32_t height1 = e_WR.getHeight();

	auto size = e_WR.getSize();

	int32_t width2 = size.x;
	int32_t height2 = size.y;

	int32_t cat = e_WR.getCategoryFlags();
	Engine::EventType type = e_WR.getEventType();
	Engine::EventType staticType = e_WR.getStaticType();

	EXPECT_EQ(width1, 800);
	EXPECT_EQ(width2, 800);
	EXPECT_EQ(height1, 600);
	EXPECT_EQ(height2, 600);
	EXPECT_EQ(cat, 1);
	EXPECT_TRUE(e_WR.isInCateogory(Engine::EventCategory::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowResize);

}

TEST(Events, MovedConstructor)
{
	Engine::e_WindowMoved e_WM(800, 600);

	int32_t x1 = e_WM.getXPos();
	int32_t y1 = e_WM.getYPos();

	int32_t x2 = 800;
	int32_t y2 = 600;

	int32_t cat = e_WM.getCategoryFlags();
	Engine::EventType type = e_WM.getEventType();
	Engine::EventType staticType = e_WM.getStaticType();

	EXPECT_EQ(x1, x2);
	EXPECT_EQ(y1, y2);
	EXPECT_EQ(cat, 1);
	EXPECT_TRUE(e_WM.isInCateogory(Engine::EventCategory::EventCategoryWindow));
	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowMoved);

}
