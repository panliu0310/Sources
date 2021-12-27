/*
class App extends React.Component
{
  render() {
    return <h1>Hello World</h1>;
  }
}
*/

const data = [
  {filename: "cuhk-2013.jpg", year: 2013, remarks: "Sunset over CUHK"},
  {filename: "cuhk-2017.jpg", year: 2017, remarks: "Bird's-eye view of CUHK"},
  {filename: "sci-2013.jpg", year: 2013, remarks: "The CUHK Emblem"},
  {filename: "shb-2013.jpg", year: 2013, remarks: "The Engineering Buildings"},
  {filename: "stream-2009.jpg", year: 2009, remarks: "Nature hidden in the campus"},
];

class Header extends React.Component {
  render() {
    return (
      <header className="bg-warning">
      <h1 className="display-4 textcenter">{this.props.name}</h1>
      </header>
    );
  /* <header> here is an HTML tag! */
  }
}

class FileCard extends React.Component {

  constructor(props)
  {
    super(props);
    this.state = { selected: -1 };
  }

  handleClick(index, e) {
    this.setState({ selected: -1 });
    if (this.state.selected != index)
      this.setState({ selected: index});
    else
      this.setState({ selected: -1 });
    console.log(index);
    console.log(this.state.selected);
  }

  render() {
    //var file = data[0];
    return (
      <>
      {data.map((file,index) => 
      <div key={index} onClick={(e) => this.handleClick(index,e)} className="card d-inline-block m-2" 
      style={{ width: this.state.selected==index ? '100%' : 200 }}>
        <img src={"images/"+file.filename} alt="{file.remarks}" className="w-100" />
        <div className="card-body">
          <h6 className="card-title">{file.filename}</h6>
          <p className="card-text">Year: {file.year}</p>
          { this.state.selected==index &&
            <p className="cardtext">{file.remarks}</p>
          }
        </div>
      </div>
      )}
      </>
    );
  }
}

class Main extends React.Component {
  render() {
    return (
    <main className="container">
    
    <FileCard />

    </main> /* Main vs main? */
    );
  }
}

class App extends React.Component {
  render() {
    return (
  <> 
  <Header name={this.props.name}/>
  <Main/>
  </> 
  );
  }
}

ReactDOM.render(
  <App name="CUHK Pictures"/>, 
  document.querySelector("#app")
);

/*
ReactDOM.render(
  <App/>,
  document.querySelector("#app")
);
*/

/*
ReactDOM.render(
  <h1>Hello World!</h1>,
  document.querySelector("#app")
);
*/