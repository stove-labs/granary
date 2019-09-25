/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// See https://docusaurus.io/docs/site-config for all the possible
// site configuration options.

// List of projects/orgs using your project for the users page.
// const users = [
//   {
//     caption: 'Stove Labs',
//     // You will need to prepend the image path with your baseUrl
//     // if it is not '/', like: '/test-site/img/docusaurus.svg'.
//     image: 'https://stove-labs.com/logo_transparent.png',
//     infoLink: 'https://stove-labs.com',
//     pinned: true,
//   },
// ];

const users = [];

const siteConfig = {
  title: 'Granary', // Title for your website.
  tagline: 'All-in toolkit for Tezos development',
  url: 'https://stove-labs.github.io/granary/', // Your website URL
  baseUrl: '/granary/', // Base URL for your project */
  // For github.io type URLs, you would set the url and baseUrl like:
  //   url: 'https://facebook.github.io',
  //   baseUrl: '/test-site/',

  // Used for publishing and more
  projectName: 'granary',
  organizationName: 'stove-labs',
  // For top-level user or org sites, the organization is still the same.
  // e.g., for the https://JoelMarcey.github.io site, it would be set like...
  //   organizationName: 'JoelMarcey'

  // For no header links in the top nav bar -> headerLinks: [],
  headerLinks: [
    {doc: 'getting-started-what-and-why', label: 'Docs'},
    {doc: 'tutorials-deploying-a-tezos-smart-contract-to-alphanet', label: 'Tutorials'},
    {doc: 'api-cli-commands', label: 'API'},
  ],

  // If you have users set above, you add it here:
  users,

  /* path to images for header/footer */
  headerIcon: 'img/grain.png',
  footerIcon: 'img/grain.png',
  favicon: 'img/grain.png',

  /* Colors for website */
  colors: {
    primaryColor: '#F0C926',
    secondaryColor: '#F0C926',
  },

  /* Custom fonts for website */
  /*
  fonts: {
    myFont: [
      "Times New Roman",
      "Serif"
    ],
    myOtherFont: [
      "-apple-system",
      "system-ui"
    ]
  },
  */

  // This copyright info is used in /core/Footer.js and blog RSS/Atom feeds.
  copyright: `Copyright © ${new Date().getFullYear()} Stove Labs`,

  highlight: {
    // Highlight.js theme to use for syntax highlighting in code blocks.
    theme: 'tomorrow-night-eighties',
  },

  // Add custom scripts here that would be placed in <script> tags.
  scripts: ['https://buttons.github.io/buttons.js'],

  // On page navigation for the current documentation page.
  onPageNav: 'separate',
  // No .html extensions for paths.
  cleanUrl: true,

  // Open Graph and Twitter card images.
  ogImage: 'img/grain.png',
  twitterImage: 'img/grain.png',

  // Show documentation's last contributor's name.
  enableUpdateBy: false,

  // Show documentation's last update time.
  enableUpdateTime: true,

  // You may provide arbitrary config keys to be used as needed by your
  // template. For example, if you need your repo's URL...
  repoUrl: 'https://github.com/stove-labs/granary',
};

module.exports = siteConfig;
