#include "server.h"
#include <gtest/gtest.h>

TEST(server, argument_proverka)
{
   char* argv[]={"6666","666","666"};
   ASSERT_EQ(2, server_init(3,argv));
}

TEST(server, proverka_connection_client)
{
   char* argv[]={"./server","3324"};
   EXPECT_NE(2, server_init(2, argv));
}

TEST(server, proverka_diapozon_more)
{
   char* argv[]={"./server","49500"};
   ASSERT_TRUE(server_init(2,argv));
}

TEST(server, proverka_diapozon_less)
{
   char* argv[]={"./server","1024"};
   ASSERT_TRUE(server_init(2,argv));
}

TEST(server, proverka_digit)
{
   char* argv[]={"./server","fffff"};
   ASSERT_TRUE(server_init(2,argv));
}

int main(int argc,char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
