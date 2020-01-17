//
// Created by timsa on 09-Dec-19.
//

#ifndef SMFL_TEST_EVENTS_H
#define SMFL_TEST_EVENTS_H

namespace Events {
/*! \enum event
 *  The event enum consists of a list of possible events that need to be communicated to the SFMLmanager
 */
enum event
{
        createView,
        expired,
        win,
        updatePlayerHealth
};

} // namespace Events
#endif // SMFL_TEST_EVENTS_H
