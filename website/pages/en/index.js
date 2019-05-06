/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

const React = require('react');

const CompLibrary = require('../../core/CompLibrary.js');

const MarkdownBlock = CompLibrary.MarkdownBlock; /* Used to read markdown */
const Container = CompLibrary.Container;
const GridBlock = CompLibrary.GridBlock;

class HomeSplash extends React.Component {
  render() {
    const {siteConfig, language = ''} = this.props;
    const {baseUrl, docsUrl} = siteConfig;
    const docsPart = `${docsUrl ? `${docsUrl}/` : ''}`;
    const langPart = `${language ? `${language}/` : ''}`;
    const docUrl = doc => `${baseUrl}${docsPart}${langPart}${doc}`;

    const SplashContainer = props => (
      <div className="homeContainer">
        <div className="homeSplashFade">
          <div className="wrapper homeWrapper">{props.children}</div>
        </div>
      </div>
    );

    const ProjectTitle = () => (
      <div>
        <h2 className="projectTitle">
        {siteConfig.title}
        <small>{siteConfig.tagline}</small>
      </h2>

      <div className="window-container is-visible animated pulse delay-1s">
        <div className="window-controls">
          <button className="window-controls-btn close-btn"></button>
          <button className="window-controls-btn minimize-btn"></button>
          <button className="window-controls-btn expand-btn"></button>
        </div>
        <div className="window-content">
          <div><span className="comment"># Setup your development environment</span> </div>
          <div><span>npm </span> i -g @stove-labs/granary@pre-alpha</div>
          <div><span>granary</span>init</div>
          <div><span className="comment"># Start a local blockchain</span> </div>
          <div><span>granary</span>node start</div>
          <div><span className="comment"># Import an account</span> </div>
          <div><span>granary</span>client - import secret key alice unencrypted:edsk3gUfU...</div>
          <div><span>granary</span>client - get balance for alice</div>
        </div>
      </div>
      </div>
    );

    const PromoSection = props => (
      <div className="section promoSection">
        <div className="promoRow">
          <div className="pluginRowBlock">{props.children}</div>
        </div>
      </div>
    );

    const Button = props => (
      <div className="pluginWrapper buttonWrapper">
        <a className="button" href={props.href} target={props.target}>
          {props.children}
        </a>
      </div>
    );

    return (
      <SplashContainer>
        <div className="inner">
          <ProjectTitle siteConfig={siteConfig} />
          <PromoSection>
            <Button href={docUrl('getting-started-what-and-why.html')}>Getting started</Button>
            <Button href={docUrl('contributors-examples.html')}>Contributing</Button>

          </PromoSection>
        </div>
      </SplashContainer>
    );
  }
}

class Index extends React.Component {
  render() {
    const {config: siteConfig, language = ''} = this.props;
    const {baseUrl} = siteConfig;

    const Block = props => (
      <Container
        padding={['bottom', 'top']}
        id={props.id}
        background={props.background}>
        <GridBlock
          align="center"
          contents={props.children}
          layout={props.layout}
        />
      </Container>
    );

    const Features = () => (
      <Block layout="threeColumn">
        {[
          {
            image: `${baseUrl}img/sand-bucket-and-shovel.png`,
            imageAlign: 'top',
            title: 'Sandboxed Blockchain',
            content: 'Full control over a local blockchain network in your hands'
          },
          {
            image: `${baseUrl}img/nautical-compass.png`,
            imageAlign: 'top',
            title: 'Integrated Block Explorer (soon™)',
            content: 'Visualize your network through a neat interface.'
          },
          {
            image: `${baseUrl}img/cruise-ship.png`,
            imageAlign: 'top',
            title: 'Contract & DAPP Deployments (soon™)',
            content: 'Keeps track of your frontend & contract deployments'
          },
        ]}
      </Block>
    );

    return (
      <div>
        <HomeSplash siteConfig={siteConfig} language={language} />
        <div className="mainContainer">
          <Features />
        </div>
      </div>
    );
  }
}

module.exports = Index;
