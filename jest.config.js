const { defaults } = require('jest-config');
module.exports = {
    ...defaults,
    "roots": ["<rootDir>/src", "<rootDir>/__tests__"],
    "watchPathIgnorePatterns": [
        "<rootDir>/granary.json",
        "<rootDir>/granary-test.json"
    ]
}