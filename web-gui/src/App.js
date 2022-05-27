import './App.css';
import AngleViewer from './Components/AngleViewer/AngleViewer';
import { AngleProvider } from './Providers/AngleProvider';

const App = () => {

  return  (
    <div className="App">
      <AngleProvider>
        <AngleViewer/>
      </AngleProvider>
      
    </div>
  );
}

export default App;
