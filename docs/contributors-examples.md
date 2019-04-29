---
id: contributors-examples
title: Examples on how to contribute to Granary
---

Contributing to Granary should be easy and straightforward, in the previous sections you learned how to setup the [development environment for contributors](contributors-development-environment.md), and [how to update the docs](contributors-updating-the-docs.md) as well.

## Opening an issue (bug/feature)

> Before assesing any potentional bug / feature, please refer to [the existing list of issues & feature requests](https://github.com/stove-labs/granary/issues).

All issues should follow the predefined issue / feature template, when you're [creating a new issue](https://github.com/stove-labs/granary/issues/new/choose), you'll be given a choice of two templates, one for bugs and one for features. Please select the appropriate one and fill it out - this helps us communicate & collaborate quicker.

## Submitting a PR for an existing issue

Once you've created the issue, or you've selected to work on an existing one, please start by forking the Granary repo. Apply fixes on your own fork, ideally following the [git-flow](https://danielkummer.github.io/git-flow-cheatsheet/) practices for branching. Once you're done proceed by creating a PR from your own fork to the main granary repo's **develop** branch.

> Please note that your PR has to pass through the preconfigured Circle CI workflow before it can be merged.


## Contribution examples

|Issue|Pull request|
|----|---|
|[**#4** NPM badge redirects to the @latest version instead of @pre-alpha](https://github.com/stove-labs/granary/issues/4)| [**#6** Fix npm badge link](https://github.com/stove-labs/granary/pull/6)


## Releases

Currently granary is released as a **pre-alpha** rolling release. Each commit to the **develop** branch issues a new npm release & git tag. Such as `1.0.0-pre-alpha.11`.