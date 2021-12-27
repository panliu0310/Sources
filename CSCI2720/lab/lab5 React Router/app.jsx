const {BrowserRouter, Link, Route, Switch} = ReactRouterDOM;
const Router = BrowserRouter;
const {useRouteMatch, useParams, useLocation} = ReactRouterDOM;

function LongLink({label, to, activeOnlyWhenExact}) {
  let match = useRouteMatch({
    path: to,
    exact: activeOnlyWhenExact
  });
  return (
    <li className={match ? "active" : ""}>
      {match && "> "}
      <Link to={to}>{label}</Link>
    </li>
  );
}

function File() {
  let { id } = useParams();
  return (
    <div>
      <h3>ID: {id}</h3>
    </div>
  );
}

function NoMatch() {
  let location = useLocation();
  return (
    <div>
      <h3>
        No match for <code>{location.pathname}</code>
      </h3>
    </div>
  );
}

class App extends React.Component {
  render() {
    return (
    <Router>
      <div>

    {/*
      <ul>
        <li>
        <Link to="/">Home</Link>
        </li>
        <li>
        <Link to="/about">About</Link>
        </li>
    	</ul>
    */}

      <ul>
        <LongLink activeOnlyWhenExact={true} to="/" label="Home"/>
        <LongLink to="/about" label="About" />

        <LongLink to="/file/fileA" label="File A" />
        <LongLink to="/file/fileB" label="File B" />
        <LongLink to="/file/fileC" label="File C" />
      </ul>

      <hr/>

      <Switch>
      	<Route exact path="/" component={Home} />
      	<Route path="/about" component={About} />
        <Route path="/file/:id" component={File} />
        <Route path="*" component={NoMatch} />
      </Switch>
      </div>
    </Router>
    );
  }
}

class Home extends React.Component {
  render() {
    return <h2>Home</h2>;
  }
}
          
class About extends React.Component {
  render() {
    return <h2>About</h2>;
  }
}

ReactDOM.render(<App/>, document.querySelector("#app"));


