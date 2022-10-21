"""Dependencies of Tink ObjC."""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tink_objc_deps():
    """Dependencies for Tink Objective C."""
    if not native.existing_rule("build_bazel_rules_apple"):
        # Release from 2022-05-02.
        http_archive(
            name = "build_bazel_rules_apple",
            sha256 = "12865e5944f09d16364aa78050366aca9dc35a32a018fa35f5950238b08bf744",
            url = "https://github.com/bazelbuild/rules_apple/releases/download/0.34.2/rules_apple.0.34.2.tar.gz",
        )
    if not native.existing_rule("build_bazel_rules_swift"):
        # Release from 2022-03-23.
        http_archive(
            name = "build_bazel_rules_swift",
            sha256 = "a2fd565e527f83fb3f9eb07eb9737240e668c9242d3bc318712efa54a7deda97",
            url = "https://github.com/bazelbuild/rules_swift/releases/download/0.27.0/rules_swift.0.27.0.tar.gz",
        )
    if not native.existing_rule("build_bazel_apple_support"):
        # Release from 2022-02-03.
        http_archive(
            name = "build_bazel_apple_support",
            sha256 = "5bbce1b2b9a3d4b03c0697687023ef5471578e76f994363c641c5f50ff0c7268",
            url = "https://github.com/bazelbuild/apple_support/releases/download/0.13.0/apple_support.0.13.0.tar.gz",
        )
