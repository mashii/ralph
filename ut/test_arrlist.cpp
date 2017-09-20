#include <gtest/gtest.h>

#include "ralph/common/arrlist.h"

TEST(arrlist, push_back)
{
    ralph::arrlist<int> al(3);
    ASSERT_EQ(0, al.size());
    ASSERT_EQ(0, al.push_back(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al.push_back(1));
    ASSERT_EQ(2, al.size());
    ASSERT_EQ(2, al.push_back(1));
    ASSERT_EQ(3, al.size());

    ASSERT_EQ(-1, al.push_back(1));
    ASSERT_EQ(3, al.size());
    ASSERT_EQ(-1, al.push_back(1));
    ASSERT_EQ(3, al.size());
    ASSERT_EQ(-1, al.push_back(1));
    ASSERT_EQ(3, al.size());

    int idx = al.head();
    ASSERT_EQ(0, idx);
    ASSERT_EQ(1, (idx = al.next(idx)));
    ASSERT_EQ(2, (idx = al.next(idx)));
    ASSERT_EQ(-1, (idx = al.next(idx)));

    idx = al.tail();
    ASSERT_EQ(2, idx);
    ASSERT_EQ(1, (idx = al.prev(idx)));
    ASSERT_EQ(0, (idx = al.prev(idx)));
    ASSERT_EQ(-1, (idx = al.prev(idx)));
}

TEST(arrlist, push_front)
{
    ralph::arrlist<int> al(3);
    ASSERT_EQ(0, al.size());
    ASSERT_EQ(0, al.push_front(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al.push_front(1));
    ASSERT_EQ(2, al.size());
    ASSERT_EQ(2, al.push_front(1));
    ASSERT_EQ(3, al.size());

    ASSERT_EQ(-1, al.push_front(1));
    ASSERT_EQ(3, al.size());
    ASSERT_EQ(-1, al.push_front(1));
    ASSERT_EQ(3, al.size());
    ASSERT_EQ(-1, al.push_front(1));
    ASSERT_EQ(3, al.size());

    int idx = al.head();
    ASSERT_EQ(2, idx);
    ASSERT_EQ(1, (idx = al.next(idx)));
    ASSERT_EQ(0, (idx = al.next(idx)));
    ASSERT_EQ(-1, (idx = al.next(idx)));

    idx = al.tail();
    ASSERT_EQ(0, idx);
    ASSERT_EQ(1, (idx = al.prev(idx)));
    ASSERT_EQ(2, (idx = al.prev(idx)));
    ASSERT_EQ(-1, (idx = al.prev(idx)));
}

TEST(arrlist, pop_front)
{
    ralph::arrlist<int> al(3);
    ASSERT_EQ(0, al.size());
    ASSERT_EQ(0, al.push_back(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al.push_back(1));
    ASSERT_EQ(2, al.size());
    ASSERT_EQ(2, al.push_back(1));
    ASSERT_EQ(3, al.size());

    al.pop_front();
    ASSERT_EQ(2, al.size());

    int idx = al.head();
    ASSERT_EQ(1, idx);
    ASSERT_EQ(2, (idx = al.next(idx)));
    ASSERT_EQ(-1, (idx = al.next(idx)));

    idx = al.tail();
    ASSERT_EQ(2, idx);
    ASSERT_EQ(1, (idx = al.prev(idx)));
    ASSERT_EQ(-1, (idx = al.prev(idx)));

    al.pop_front();
    ASSERT_EQ(1, al.size());

    idx = al.head();
    ASSERT_EQ(2, idx);
    ASSERT_EQ(-1, (idx = al.next(idx)));

    idx = al.tail();
    ASSERT_EQ(2, idx);
    ASSERT_EQ(-1, (idx = al.prev(idx)));

    al.pop_front();
    ASSERT_EQ(0, al.size());

    idx = al.head();
    ASSERT_EQ(-1, idx);

    idx = al.tail();
    ASSERT_EQ(-1, idx);

    ASSERT_EQ(2, al.push_back(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al.push_back(1));
    ASSERT_EQ(2, al.size());
    ASSERT_EQ(0, al.push_back(1));
    ASSERT_EQ(3, al.size());
}

TEST(arrlist, pop_back)
{
    ralph::arrlist<int> al(3);
    ASSERT_EQ(0, al.size());
    ASSERT_EQ(0, al.push_back(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al.push_back(1));
    ASSERT_EQ(2, al.size());
    ASSERT_EQ(2, al.push_back(1));
    ASSERT_EQ(3, al.size());

    al.pop_back();
    ASSERT_EQ(2, al.size());

    int idx = al.head();
    ASSERT_EQ(0, idx);
    ASSERT_EQ(1, (idx = al.next(idx)));
    ASSERT_EQ(-1, (idx = al.next(idx)));

    idx = al.tail();
    ASSERT_EQ(1, idx);
    ASSERT_EQ(0, (idx = al.prev(idx)));
    ASSERT_EQ(-1, (idx = al.prev(idx)));

    al.pop_back();
    ASSERT_EQ(1, al.size());

    idx = al.head();
    ASSERT_EQ(0, idx);
    ASSERT_EQ(-1, (idx = al.next(idx)));

    idx = al.tail();
    ASSERT_EQ(0, idx);
    ASSERT_EQ(-1, (idx = al.prev(idx)));

    al.pop_back();
    ASSERT_EQ(0, al.size());

    idx = al.head();
    ASSERT_EQ(-1, idx);

    idx = al.tail();
    ASSERT_EQ(-1, idx);

    ASSERT_EQ(0, al.push_back(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al.push_back(1));
    ASSERT_EQ(2, al.size());
    ASSERT_EQ(2, al.push_back(1));
    ASSERT_EQ(3, al.size());
}

TEST(arrlist, pop)
{
    ralph::arrlist<int> al(3);
    ASSERT_EQ(0, al.size());
    ASSERT_EQ(0, al.push_back(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al.push_back(1));
    ASSERT_EQ(2, al.size());
    ASSERT_EQ(2, al.push_back(1));
    ASSERT_EQ(3, al.size());

    al.pop(1);
    ASSERT_EQ(2, al.size());

    int idx = al.head();
    ASSERT_EQ(0, idx);
    ASSERT_EQ(2, (idx = al.next(idx)));
    ASSERT_EQ(-1, (idx = al.next(idx)));

    idx = al.tail();
    ASSERT_EQ(2, idx);
    ASSERT_EQ(0, (idx = al.prev(idx)));
    ASSERT_EQ(-1, (idx = al.prev(idx)));

    al.pop(0);
    ASSERT_EQ(1, al.size());

    idx = al.head();
    ASSERT_EQ(2, idx);
    ASSERT_EQ(-1, (idx = al.next(idx)));

    idx = al.tail();
    ASSERT_EQ(2, idx);
    ASSERT_EQ(-1, (idx = al.prev(idx)));

    al.pop(2);
    ASSERT_EQ(0, al.size());

    idx = al.head();
    ASSERT_EQ(-1, idx);

    idx = al.tail();
    ASSERT_EQ(-1, idx);

    ASSERT_EQ(2, al.push_back(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(0, al.push_back(1));
    ASSERT_EQ(2, al.size());
    ASSERT_EQ(1, al.push_back(1));
    ASSERT_EQ(3, al.size());
}

TEST(arrlist, move_tail)
{
    {
        ralph::arrlist<int> al(1);
        ASSERT_EQ(0, al.push_back(1));

        ASSERT_EQ(1, al[0]);

        al.move_tail(0);

        ASSERT_EQ(1, al[0]);

        int idx = al.head();
        ASSERT_EQ(0, idx);
        ASSERT_EQ(-1, (idx = al.next(idx)));

        idx = al.tail();
        ASSERT_EQ(0, idx);
        ASSERT_EQ(-1, (idx = al.prev(idx)));
    }


    {
        ralph::arrlist<int> al(2);
        ASSERT_EQ(0, al.push_back(0));
        ASSERT_EQ(1, al.push_back(1));

        ASSERT_EQ(0, al[0]);
        ASSERT_EQ(1, al[1]);

        al.move_tail(0);

        ASSERT_EQ(0, al[0]);
        ASSERT_EQ(1, al[1]);

        int idx = al.head();
        ASSERT_EQ(1, idx);
        ASSERT_EQ(0, (idx = al.next(idx)));
        ASSERT_EQ(-1, (idx = al.next(idx)));

        idx = al.tail();
        ASSERT_EQ(0, idx);
        ASSERT_EQ(1, (idx = al.prev(idx)));
        ASSERT_EQ(-1, (idx = al.prev(idx)));
    }


    {
        ralph::arrlist<int> al(3);
        ASSERT_EQ(0, al.push_back(0));
        ASSERT_EQ(1, al.push_back(1));
        ASSERT_EQ(2, al.push_back(2));

        ASSERT_EQ(0, al[0]);
        ASSERT_EQ(1, al[1]);
        ASSERT_EQ(2, al[2]);

        al.move_tail(1);

        ASSERT_EQ(0, al[0]);
        ASSERT_EQ(1, al[1]);
        ASSERT_EQ(2, al[2]);

        int idx = al.head();
        ASSERT_EQ(0, idx);
        ASSERT_EQ(2, (idx = al.next(idx)));
        ASSERT_EQ(1, (idx = al.next(idx)));
        ASSERT_EQ(-1, (idx = al.next(idx)));

        idx = al.tail();
        ASSERT_EQ(1, idx);
        ASSERT_EQ(2, (idx = al.prev(idx)));
        ASSERT_EQ(0, (idx = al.prev(idx)));
        ASSERT_EQ(-1, (idx = al.prev(idx)));
    }

}

TEST(arrlist, move_head)
{
    {
        ralph::arrlist<int> al(1);
        ASSERT_EQ(0, al.push_back(1));

        ASSERT_EQ(1, al[0]);

        al.move_head(0);

        ASSERT_EQ(1, al[0]);

        int idx = al.head();
        ASSERT_EQ(0, idx);
        ASSERT_EQ(-1, (idx = al.next(idx)));

        idx = al.tail();
        ASSERT_EQ(0, idx);
        ASSERT_EQ(-1, (idx = al.prev(idx)));
    }


    {
        ralph::arrlist<int> al(2);
        ASSERT_EQ(0, al.push_back(0));
        ASSERT_EQ(1, al.push_back(1));

        ASSERT_EQ(0, al[0]);
        ASSERT_EQ(1, al[1]);

        al.move_head(1);

        ASSERT_EQ(0, al[0]);
        ASSERT_EQ(1, al[1]);

        int idx = al.head();
        ASSERT_EQ(1, idx);
        ASSERT_EQ(0, (idx = al.next(idx)));
        ASSERT_EQ(-1, (idx = al.next(idx)));

        idx = al.tail();
        ASSERT_EQ(0, idx);
        ASSERT_EQ(1, (idx = al.prev(idx)));
        ASSERT_EQ(-1, (idx = al.prev(idx)));
    }


    {
        ralph::arrlist<int> al(3);
        ASSERT_EQ(0, al.push_back(0));
        ASSERT_EQ(1, al.push_back(1));
        ASSERT_EQ(2, al.push_back(2));

        ASSERT_EQ(0, al[0]);
        ASSERT_EQ(1, al[1]);
        ASSERT_EQ(2, al[2]);

        al.move_head(1);

        ASSERT_EQ(0, al[0]);
        ASSERT_EQ(1, al[1]);
        ASSERT_EQ(2, al[2]);

        int idx = al.head();
        ASSERT_EQ(1, idx);
        ASSERT_EQ(0, (idx = al.next(idx)));
        ASSERT_EQ(2, (idx = al.next(idx)));
        ASSERT_EQ(-1, (idx = al.next(idx)));

        idx = al.tail();
        ASSERT_EQ(2, idx);
        ASSERT_EQ(0, (idx = al.prev(idx)));
        ASSERT_EQ(1, (idx = al.prev(idx)));
        ASSERT_EQ(-1, (idx = al.prev(idx)));
    }

}

TEST(arrlist, operator_square_brace)
{
    ralph::arrlist<int> al(3);
    ASSERT_EQ(3, al.capacity());
    ASSERT_EQ(0, al.size());
    ASSERT_EQ(0, al.push_back(1));
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al[0]);
    al[0] = 3;
    ASSERT_EQ(3, al[0]);
    ASSERT_EQ(3, al.capacity());
    ASSERT_EQ(1, al.size());
}

TEST(arrlist, copy_structor)
{
    ralph::arrlist<int> al(3);
    ASSERT_EQ(0, al.push_back(1));
    ralph::arrlist<int> n(al);

    ASSERT_EQ(3, al.capacity());
    ASSERT_EQ(1, al.size());
    ASSERT_EQ(1, al[0]);

    ASSERT_EQ(3, n.capacity());
    ASSERT_EQ(1, n.size());
    ASSERT_EQ(1, n[0]);
}

TEST(arrlist, move_structor)
{
    ralph::arrlist<int> al(3);
    ASSERT_EQ(0, al.push_back(1));
    ralph::arrlist<int> n(std::move(al));

    ASSERT_EQ(3, n.capacity());
    ASSERT_EQ(1, n.size());
    ASSERT_EQ(1, n[0]);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
