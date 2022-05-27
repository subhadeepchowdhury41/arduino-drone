import React from 'react';
import { useAngleContext } from '../../Providers/AngleProvider';

const AngleViewer = () => {

    const {angle} = useAngleContext();

    return (
        <div>
            {angle}
        </div>
    );
}

export default AngleViewer;