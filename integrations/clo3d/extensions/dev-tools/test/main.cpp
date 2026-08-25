#include <gtest/gtest.h>
#include <QApplication>

#if (defined(__has_feature) && __has_feature(address_sanitizer)) || defined(__SANITIZE_ADDRESS__)
  #if defined(__has_include) && !defined(_MSC_VER) && __has_include(<sanitizer/lsan_interface.h>)
    #include <sanitizer/lsan_interface.h>
    #define HAS_LSAN 1
  #endif
#endif

int main(int argc, char** argv) {
    int result = 0;
    {
        qputenv("QT_QPA_PLATFORM", "offscreen");
#if defined(HAS_LSAN)
        __lsan_disable();
#endif
        QApplication app(argc, argv);
#if defined(HAS_LSAN)
        __lsan_enable();
#endif
        ::testing::InitGoogleTest(&argc, argv);
        result = RUN_ALL_TESTS();
    }
    return result;
}