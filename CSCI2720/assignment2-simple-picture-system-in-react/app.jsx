const data = [
  {filename: "cuhk-2013.jpg", year: 2013, remarks: "Sunset over CUHK"},
  {filename: "cuhk-2017.jpg", year: 2017, remarks: "Bird's-eye view of CUHK"},
  {filename: "sci-2013.jpg", year: 2013, remarks: "The CUHK Emblem"},
  {filename: "shb-2013.jpg", year: 2013, remarks: "The Engineering Buildings"},
  {filename: "stream-2009.jpg", year: 2009, remarks: "Nature hidden in the campus"},
];

const {BrowserRouter, Link, Route, Switch} = ReactRouterDOM;
const Router = BrowserRouter;
const {useRouteMatch, useParams, useLocation} = ReactRouterDOM;

class Header extends React.Component {
  render() {
    return (
      <header className="bg-warning">
      <h1 className="display-4 textcenter">{this.props.name}</h1>
      </header>
    );
  }
}

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

class Home extends React.Component {
  render() {
    return (
      <div className="d-inline-block m-2">
        <h2>Home</h2>
        <img src={"assignment2.jpg"} />
      </div>
    );
  }
}

class Main extends React.Component {
  render() {
    return (
    <main className="container">
    
    <FileCard />

    </main>
    );
  }
}

function File() {
  let { id } = useParams();
  return (
    <div className="d-inline-block m-2" style={{ width: '100%' }}>
      <img src={"../images/"+data[id].filename} alt="{data[id].remarks}" className="w-100" />
      <p className="cardtext">{data[id].filename}</p>
      <p className="card-text">Year: {data[id].year}</p>
      <p className="cardtext">{data[id].remarks}</p>
    </div>
  );
  
}

class FileCard extends React.Component {

  constructor(props)
  {
    super(props);
    this.state = { selected: -1 };
  }

  handleMouseOver(index) {
    this.setState({ selected: index });
  }

  handleMouseOut() {
    this.setState({ selected: -1 });
  }

  render() {
    return (
      <Router>
      {data.map((file,index) => 
      <div key={index} onMouseOver={() => this.handleMouseOver(index)} 
      onMouseOut={() => this.handleMouseOut()}
      className="card d-inline-block m-2" 
      style={{ width: this.state.selected==index ? 220 : 200 }}>
        <img src={"images/"+file.filename} alt="{file.remarks}" className="w-100" />
        <div className="card-body">
          <h6 className="card-title">
            <Link to={"/file/"+index}>{file.filename}</Link> 
          </h6>
          <p className="card-text">Year: {file.year}</p>
          { this.state.selected==index &&
            <p className="cardtext">{file.remarks}</p>
          }
        </div>
      </div>
      )}
      <div>
        <Switch>
          <Route path="/file/:id" component={File} />
        </Switch>
      </div>
      </Router>
    );
  }
}

var intervalHandle = null;

class Slideshow extends React.Component {

  constructor(props)
  {
    super(props);
    this.state = 
    { currentImageID: 0 ,
      currentInterval: 1000
    };
  }

  startSlideshow() {
    clearInterval(intervalHandle);
    intervalHandle = setInterval(() => {
      this.setState({ currentImageID: this.state.currentImageID == 4 ? 0 : this.state.currentImageID + 1 });
      console.log(this.state.currentImageID + ' ' + this.state.currentInterval);
    }, this.state.currentInterval);
  }

  stopSlideshow() {
    clearInterval(intervalHandle);
  }

  slower() {
    this.stopSlideshow();
    this.setState({ currentInterval: this.state.currentInterval * 2 });
    this.startSlideshow();
  }

  faster() {
    this.stopSlideshow();
    this.setState({ currentInterval: this.state.currentInterval / 2 });
    this.startSlideshow();
  }

  render() {
    return (
    <div className="d-inline-block m-2 p-3">
      <button onClick={() => this.startSlideshow()}>Start slideshow</button>
      <button onClick={() => this.stopSlideshow()}>Stop slideshow</button>
      <button onClick={() => this.slower()}>Slower</button>
      <button onClick={() => this.faster()}>Faster</button>
      <img src={"images/"+data[this.state.currentImageID].filename} className="w-100" />
    </div>
    );
  }
}

class RouterClass extends React.Component {
  render() {
    return (
    <Router>
      <div>
      <ul>
        <LongLink activeOnlyWhenExact={true} to="/" label="Home"/>
        <LongLink to="/file" label="Images" />
        <LongLink to="/slideshow" label="Slideshow" />
      </ul>

      <hr/>

      <Switch>
      	<Route exact path="/" component={Home} />
      	<Route path="/file" component={Main} />
        <Route path="/slideshow" component={Slideshow} />
        <Route path="*" component={NoMatch} />
      </Switch>
      </div>
    </Router>
    );
  }
}

class App extends React.Component {
  render() {
    return (
  <> 
  <Header name={this.props.name}/>
  <RouterClass />
  </> 
  );
  }
}

ReactDOM.render(
  <App name="CUHK Pictures"/>, 
  document.querySelector("#app")
);