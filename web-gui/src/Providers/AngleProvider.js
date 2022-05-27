import { useState, createContext, useContext} from 'react';
import { useInterval } from '../Utils/CustomHooks';

const AngleContext = createContext();

export const AngleProvider = ({children}) => {
    
    const [angle, setAngle] = useState(0);

    const handleChange = () => {
        setAngle(angle + 1);
    }

    useInterval(() => {
        handleChange();
    }, 1000);
    
    
    return (
        <AngleContext.Provider value={{angle}}>
            {children}
        </AngleContext.Provider>
    );
}

export const useAngleContext = () => {
    return useContext(AngleContext);
}