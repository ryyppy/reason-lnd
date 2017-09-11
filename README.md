# TicTacToe as a Service

This is a fullstack TicTacToe application with a dedicated OCaml server and
ReasonML-based frontend.

## Initial Setup

**To get the app running on the first try, build the frontend first:**

```
cd frontend
yarn install
npm run build
npm run webpack
```

**After that, build and run the backend:**

```
cd backend
make build
make run
```

Now the backend will serve the content of `frontend/public/index.html` and `frontend/bundledOutputs/app.js`.
You can access the application with `http://localhost:8000/public/index.html`.
