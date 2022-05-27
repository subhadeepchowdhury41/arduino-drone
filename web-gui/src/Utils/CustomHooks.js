import { useEffect, useRef } from "react";

export const useInterval = (callback, delay) => {

    const savedCallback = useRef(callback);

    useEffect(() => {
        savedCallback.current = callback;
    }, [callback]);

    useEffect(() => {
      const tick = () => {
          savedCallback.current();
      }

      if (!delay && delay !== 0) {
          return;
      }

      const id = setInterval(() => {
          tick();
      }, delay);
    
      return () => {
        clearInterval(id);
      }
    }, [delay])
    
}