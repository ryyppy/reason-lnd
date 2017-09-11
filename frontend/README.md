This is a repo with examples usages of [ReasonReact](https://github.com/reasonml/reason-react).
Have something you don't understand? Join us on [Discord](https://discord.gg/reasonml)!

## Setup

If you are using the `npm` workflow, just follow the official [installation guide](https://reasonml.github.io/guide/editor-tools/global-installation):

For those who are using `opam` for your editor integration, make sure to use the correct switch and packages:

```
opam switch 4.02.3
opam install reason.1.13.6
opam install merlin.2.5.4
```

## Build & Run

```
yarn install

# in one tab
npm start

# in another tab
npm run webpack:watch
```

Now you should see build artifacts in `bundledOutputs`.


Make sure to use the backend to load the application...
the `public/index.html` will not work as a local file.
