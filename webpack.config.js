const path = require("path");

module.exports = {
    mode: "development",
    entry: {
        test1: "./test/Test1.bs.js",

    },
    output: {
        filename: "[name].js",
        path: path.resolve(__dirname, "test_dist")
    }
};