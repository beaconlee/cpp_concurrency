load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
    name = "refresh",
    # 指定目标 target 及其编译选项/参数（.bazelrc 中已有的参数/选项无需重复添加）
    targets = {
        "//concurrency/thread_management:thread_create": "",
    },
)
