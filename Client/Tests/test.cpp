#include "pch.h"
#include "../Client/TranslateText.h"
TEST(TranslateTestCase, TranslateText) {
  EXPECT_EQ(TranslateText::Translate("text", "ru"), "текст");
  EXPECT_TRUE(true);
}